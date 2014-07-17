#include "codegen.h"
#include <sstream>




// intをstringに変換する関数
string IntToString(int number)
{
  stringstream ss;
  ss << number;
  return ss.str();
}



Code::Code(string tag0, string tag1, string tag2, bool flag) {
  tag[0] = tag0;
  tag[1] = tag1;
  tag[2] = tag2;
  label_flag = flag;
}

string Code::form_code() {
  string ret;
  if (label_flag) {
    // もしラベルなら次のように出力する
    // (e.g.) label:
    ret = tag[0] + ":";
  } else {
    //ラベルでないなら次のように出力する
    // (e.g.) \tadd\tesp,eax
    if (tag[2] != "") {
      ret = "\t" + tag[0] + "\t" + tag[1] + "," + tag[2];
    } else {
      ret = "\t" + tag[0] + "\t" + tag[1];
    }
  }
  return ret;
}

string Code::get_tag(int num) {
  return tag[num];
}

bool Code::is_label() {
  return label_flag;
}




CodeGen::CodeGen(TC::Token_Driver *td, ostream *o) : out(o), label(0) {
}

void CodeGen::code_generate(NodeList *nl) {
  for (int i = 0; i < nl->get_size(); i++) {
    switch(nl->get_node(i)->get_type()) {
      case OP::FUNCNODE:
        func_decl_gen( (FuncNode *)(nl->get_node(i)) );
        break;
      case OP::DECLTYPENODE:
        external_decl_gen( (DeclTypeNode *)(nl->get_node(i)) );
        break;
    }
  }
}


void CodeGen::external_decl_gen(DeclTypeNode *dtn) {
  DeclList *dl = (DeclList *)(dtn->getlist());

  for (int i = 0; i < dl->get_elems_size(); i++) {
    IdentifierNode *id = (IdentifierNode *)(dl->get_elems_node(i));
    // emit_code("\tCOMMON\t" + id->getname() + "\t" + IntToString(4));
    emit_code(new Code("COMMON", id->getname() + "\t" + IntToString(4)));
  }
}

void CodeGen::func_decl_gen(FuncNode *fn) {
  // top_allocセット
  final_temp_alloc = top_alloc = -(fn->get_count());

  // returnラベルの生成
  ret_label = "Lret_" + fn->getnode(1)->getname();

  // fnのnode_[1] = IdentiferNode
  // emit_code("\tGLOBAL\t" + fn->getnode(1)->getname());
  emit_code(new Code("GLOBAL", fn->getnode(1)->getname()));
  // emit_code(fn->getnode(1)->getname() + ":");
  emit_code(new Code(fn->getnode(1)->getname(), "", "", true));
  // emit_code("\tpush\tebp");
  emit_code(new Code("push", "ebp", ""));
  // emit_code("\tmov\tebp,esp");
  emit_code(new Code("mov", "ebp", "esp"));

  // 挿入位置をマークしておく
  // emit_code("TEMP_ALLOC_CODE");
  emit_code(new Code("TEMP_ALLOC_CODE", "", ""));


  // 関数本体のコード
  state_list_gen((StatList *)(((ComStatNode *)(fn->getnode(3)))->get_list(1)));

  // emit_code(ret_label + ":");
  emit_code(new Code(ret_label, "", "", true));
  // emit_code("\tmov\tesp,ebp");
  emit_code(new Code("mov", "esp", "ebp"));
  // emit_code("\tpop\tebp");
  emit_code(new Code("pop", "ebp", ""));
  // emit_code("\tret");
  emit_code(new Code("ret", "", ""));

  // 一時変数分確保する
  insert_temp_alloc_code();
}

void CodeGen::state_list_gen(StatList *sl) {
  for (int i = 0; i < sl->get_elems_size(); i++) {
    Node *n = sl->get_elems_node(i);
    state_gen(n);
  }
}

void CodeGen::state_gen(Node *n) {
  switch(n->get_type()) {
      case(OP::STATNODE):
        if (n->getnode(0) != NULL) {
          expr_list_gen((ExpressionList *)(n->getnode(0)));
        }
        break;
      case(OP::COMSTATNODE):
        state_list_gen((StatList *)(((ComStatNode *)n)->get_list(1)));
        break;
      case(OP::IFSTATNODE):
        if_state_gen((IFStatNode *)n, false);
        break;
      case(OP::IFELSESTATNODE):
        if_state_gen((IFStatNode *)n, true);
        break;
      case(OP::WHILESTATNODE):
        while_state_gen((WHILEStatNode *)n);
        break;
      case(OP::RETSTATNODE):
        ret_state_gen((RETURNStatNode *)n);
        break;
    }
}

void CodeGen::if_state_gen(IFStatNode *isn, bool isElse) {
  string L1, L2;
  L1 = make_label();
  if (isElse == false) {
    // else節が存在しないならば
    //条件式コードの生成 結果が偽ならばl1にジャンプ
    expr_list_gen((ExpressionList *)(isn->getnode(0)));

    // emit_code("\tcmp\teax,0");
    emit_code(new Code("cmp", "eax", "0"));
    // emit_code("\tje\t" + L1);
    emit_code(new Code("je", L1, ""));
    //本体コードの生成
    state_gen(isn->getnode(1));
    // emit_code(L1 + ":");
    emit_code(new Code(L1, "", "", true));

  } else {
    // else節が存在するならば 
    L2 = make_label();
    // 条件式コードの生成 結果が偽ならばL1へジャンプ
    expr_list_gen((ExpressionList *)(isn->getnode(0)));

    // emit_code("\tcmp\teax,0");
    emit_code(new Code("cmp", "eax", "0"));
    // emit_code("\tje\t" + L1);
    emit_code(new Code("je", L1, ""));
    // if節のコード生成
    state_gen(isn->getnode(1));
    // emit_code("\tjmp\t" + L2);
    emit_code(new Code("jmp", L2, ""));
    // emit_code(L1 + ":");
    emit_code(new Code(L1, "", "", true));
    // else節のコード生成
    state_gen(isn->getnode(2));
    // emit_code(L2 + ":");
    emit_code(new Code(L2, "", "", true));
  }
}

void CodeGen::while_state_gen(WHILEStatNode *wsn) {
  string s = make_label();
  string e = make_label();

  // emit_code(s + ":");
  emit_code(new Code(s, "", "", true));
  // 条件式コード生成
  expr_list_gen((ExpressionList *)(wsn->getnode(0)));

  // emit_code("\tcmp\teax,0");
  emit_code(new Code("cmp", "eax", "0"));
  // emit_code("\tje\t" + e);
  emit_code(new Code("je", e, ""));
  // 本体のコード生成
  state_gen(wsn->getnode(1));

  // emit_code("\tjmp\t" + s);
  emit_code(new Code("jmp", s, ""));
  // emit_code(e + ":");
  emit_code(new Code(e, "", "", true));

}


void CodeGen::ret_state_gen(RETURNStatNode *rsn) {
  // 式の計算コード生成
  expr_list_gen((ExpressionList *)(rsn->getnode(0)));

  // emit_code("\tjmp\t" + ret_label);
  emit_code(new Code("jmp", ret_label, ""));
}



void CodeGen::expr_list_gen(ExpressionList *epl) {
  assign_expr_gen((AssignExprNode *)(epl->getnode(0)));
  if (epl->getnode(1) != NULL) {
    expr_list_gen((ExpressionList *)(epl->getnode(1)));
  }
}



void CodeGen::assign_expr_gen(AssignExprNode *aen) {
  string c,t0,t1,t2;
  // 左辺に変数をもつ場合
  if (aen->getnode(0) != NULL) {
    // 右辺の実行
    assign_expr_gen((AssignExprNode *)(aen->getnode(1)));
    // 指定の番地に値を戻す
    IdentifierNode *n = (IdentifierNode *)(aen->getnode(0));

    // 大域変数の場合
    if (n->get_token_info()->get_lev() == 0) {
      // emit_code("\tmov\t[" + n->getname() + "],eax");
      emit_code(new Code("mov", "[" + n->getname() + "]", "eax"));
    } else {
      t0 = "mov";
      t1 = "[ebp";
      // c = "\tmov\t[ebp";
      if (n->get_offset_from_node() > 0) {
        // c += "+";
        t1 += "+";
      }
      // c += IntToString(n->get_offset_from_node()) + "],eax";
      t1 += IntToString(n->get_offset_from_node()) + "]";
      t2 = "eax";
      // emit_code(c);
      emit_code(new Code(t0, t1, t2));
    }
  } else {
    expr_gen(aen->getnode(1));
  }
}


void CodeGen::general_expr_gen(string expr, Node *n) {
  int tmp;
  expr_gen(n->getnode(1));
  // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
  emit_code(new Code("mov", "[ebp-" + IntToString(tmp=create_temp_alloc()) + "]", "eax"));
  expr_gen(n->getnode(0));
  // emit_code("\t" + expr + "\teax,[ebp-" + IntToString(tmp) + "]");
  emit_code(new Code(expr, "eax", "[ebp-" + IntToString(tmp) + "]"));
  release_temp();
}

void CodeGen::general_cmp_gen(string cmp, Node *n) {
  int tmp;
  expr_gen(n->getnode(1));
  // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
  emit_code(new Code("mov", "[ebp-" + IntToString(tmp=create_temp_alloc()) + "]", "eax"));
  expr_gen(n->getnode(0));
  // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
  emit_code(new Code("cmp", "eax", "[ebp-" + IntToString(tmp) + "]"));
  // emit_code("\t" + cmp + "\tal");
  emit_code(new Code(cmp, "al", ""));
  // emit_code("\tmovzx\teax,al");
  emit_code(new Code("movzx", "eax", "al"));
  release_temp();
}

void CodeGen::general_logical_gen(string logical, Node *n) {
  int tmp;
  string label = make_label();


  // emit_code("\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "],0");
  emit_code(new Code("mov", "dword [ebp-" + IntToString(tmp=create_temp_alloc()) + "]", logical == "OR" ? "1" : "0"));
  expr_gen(n->getnode(0));
  // emit_code("\tcmp\teax,0");
  emit_code(new Code("cmp", "eax", "0"));
  // emit_code("\tje\t" + label);
  emit_code(new Code("je", label, ""));
  expr_gen(n->getnode(1));
  // emit_code("\tcmp\teax,0");
  emit_code(new Code("cmp", "eax", "0"));
  // emit_code("\tje\t" + label);
  emit_code(new Code("je", label, ""));
  // emit_code("\tmov\tdword [ebp-" + IntToString(tmp) + "],1");
  emit_code(new Code("mov", "dword [ebp-" + IntToString(tmp) + "]", logical == "OR" ? "0" : "1"));
  // emit_code(label + ":");
  emit_code(new Code(label, "", "", true));
  // emit_code("\tmov\teax,[ebp-" + IntToString(tmp) + "]");
  emit_code(new Code("mov", "eax", "[ebp-" + IntToString(tmp) + "]"));
}

// void CodeGen::general_logical_and_gen(Node *n) {
//   string label = make_label();
//   emit_code(new Code("mov", "dword [ebp-" + IntToString(tmp=create_temp_alloc()) + "]", "0"));
//   expr_gen(n->getnode(0));
//   emit_code(new Code("cmp", "eax", "0"));
//   emit_code(new Code("setne", "al", ""));
//   emit_code(new Code("movzx", "eax", "al"));
//   emit_code(new Code())
//   expr_gen(n->getnode(1));
//   emit_code(new Code("cmp", "eax", "0"));
//   emit_code(new Code("setne", "al", ""));
//   emit_code(new Code("movzx", "eax", "al"))

// }

void CodeGen::expr_gen(Node *n) {
  string c, label, t0, t1, t2;
  IdentifierNode *in;
  int op = n->getop();
  int tmp;
  switch(op) {

    case OP::ADD:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tadd\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("add", n);
      break;


    case OP::SUB:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tsub\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("sub", n);
      break;


    case OP::MUL:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\timul\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("imul", n);
      break;


    case OP::DIV:
      expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      emit_code(new Code("mov", "[ebp-" + IntToString(tmp=create_temp_alloc()) + "]", "eax"));
      expr_gen(n->getnode(0));
      // emit_code("\tcdq");
      emit_code(new Code("cdq", "", ""));
      // emit_code("\tidiv\tdword [ebp-" + IntToString(tmp) + "]");
      emit_code(new Code("idiv", "dword [ebp-" + IntToString(tmp) + "]", ""));
      release_temp();
      break;

    case OP::BITOR:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tor\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("or", n);
      break;

    case OP::BITXOR:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\txor\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("xor", n);
      break;

    case OP::BITAND:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tand\teax,[ebp-" + IntToString(tmp) + "]");
      // release_temp();
      general_expr_gen("and", n);
      break;

    case OP::GREATEREQUAL:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsetge\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("setge", n);
      break;


    case OP::LESSEQUAL:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsetle\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("setle", n);
      break;

    case OP::EQUAL:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsete\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("sete", n);
      break;


    case OP::NOTEQUAL:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsetne\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("setne", n);
      break;


    case OP::LESS:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsetl\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("setl", n);
      break;


    case OP::GREATER:
      // expr_gen(n->getnode(1));
      // emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      // emit_code("\tsetg\tal");
      // emit_code("\tmovzx\teax,al");
      // release_temp();
      general_cmp_gen("setg", n);
      break;


    case OP::OR:
      // label = make_label();
      // emit_code("\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "],0");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,0");
      // emit_code("\tje\t" + label);
      // expr_gen(n->getnode(1));
      // emit_code("\tcmp\teax,0");
      // emit_code("\tje\t" + label);
      // emit_code("\tmov\tdword [ebp-" + IntToString(tmp) + "],1");
      // emit_code(label + ":");
      // emit_code("\tmov\teax,[ebp-" + IntToString(tmp) + "]");
      general_logical_gen("OR", n);
      break;

    case OP::AND:
      // label = make_label();
      // emit_code("\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "],1");
      // expr_gen(n->getnode(0));
      // emit_code("\tcmp\teax,0");
      // emit_code("\tjne\t" + label);
      // expr_gen(n->getnode(1));
      // emit_code("\tcmp\teax,0");
      // emit_code("\tjne\t" + label);
      // emit_code("\tmov\tdword [ebp-" + IntToString(tmp) + "],0");
      // emit_code(label + ":");
      // emit_code("\tmov\teax,[ebp-" + IntToString(tmp) + "]");
      general_logical_gen("AND", n);
      break;

    case OP::ID:
      in = (IdentifierNode *)n;
      if (in->get_token_info()->get_lev() == 0) {
        // emit_code("\tmov\teax, [" + in->getname() + "]");
        emit_code(new Code("mov", "eax", "[" + in->getname() + "]"));
      } else {
        t0 = "mov";
        t1 = "eax";
        t2 = "[ebp";
        // c = "\tmov\teax, [ebp";
        if (in->get_offset_from_node() > 0) {
          // c += "+";
          t2 += "+";
        }
        // c += IntToString(in->get_offset_from_node()) + "]";
        t2 += IntToString(in->get_offset_from_node()) + "]";
        // emit_code(c);
        emit_code(new Code(t0, t1, t2));
      }
      break;

    case OP::INTEGER:
      // emit_code("\tmov\teax," + IntToString(n->getvalue()));
      emit_code(new Code("mov", "eax", IntToString(n->getvalue())));
      break;

    case OP::FUNCCALL:
      func_call_gen((FuncCallNode *)n);
      break;

    case OP::UNARY:
      expr_gen(n->getnode(0));
      // emit_code("\timul\teax, -1");
      emit_code(new Code("imul", "eax", "-1"));
      break;

    case OP::EXPRESSION:
      expr_list_gen( (ExpressionList *)n );
      break;
  }
}

void CodeGen::func_call_gen(FuncCallNode *fcn) {
  IdentifierNode *id = (IdentifierNode *)(fcn->getnode(0));
  FuncArgsList *args = (FuncArgsList *)(fcn->getlist());

  // UNDEFFUNならば
  if (id->get_token_info()->get_kind() == TC::TkInfo::UNDEFFUN) {
    // emit_code("EXTERN\t" + id->getname());
    emit_code(new Code("EXTERN", id->getname(), ""));
  }

  // 引数をスタックに積んでいく.
  for (int i = args->get_elems_size()-1; i >= 0 ; i--) {
    assign_expr_gen( ( AssignExprNode * )(args->get_elems_node(i)) );
    // emit_code("\tpush\teax");
    emit_code(new Code("push", "eax", ""));
  }
  // emit_code("\tcall\t" + id->getname());
  emit_code(new Code("call", id->getname(), ""));
  // スタックポイントを戻しておく
  // emit_code("\tadd\tesp," + IntToString(4 * args->get_elems_size()));
  emit_code(new Code("add", "esp", IntToString(4 * args->get_elems_size())));
}



/*
 *                            コード出力関係
 */

void CodeGen::emit_code(Code *c) {
  codes.push_back(c);
}

string CodeGen::make_label() {
  string ret = "L" + IntToString(label++);
  return ret;
}

void CodeGen::release_code() {
  // 出力する前に最適化を行う
  //optimize_code();

  // コードをostreamに出力する
  for (int i = 0; i < codes.size(); i++) {
    // (*out) << codes[i] << endl;
    if (codes[i] != NULL) {
      (*out) << codes[i]->form_code() << endl;
    }
  }
}


int CodeGen::create_temp_alloc() {
  top_alloc+=4;
  if (top_alloc > final_temp_alloc) {
    final_temp_alloc = top_alloc;
  }
  return top_alloc;
}

void CodeGen::insert_temp_alloc_code() {
  // 最新の関数に対して行う必要があるので末尾から探索する
  for (int i = codes.size() - 1; i >= 0; i--) {
    if (codes[i]->get_tag(0) == "TEMP_ALLOC_CODE") {
      // codes[i] = "\tsub\tesp," + IntToString(final_temp_alloc);
      codes[i] = new Code("sub", "esp", IntToString(final_temp_alloc));
    }
  }
}

void CodeGen::optimize_code() {
  Code *c1, *c2;
  for (int i = 0; i < codes.size() - 1; i++) {
    c1 = codes[i];
    c2 = codes[i+1];
    if (c1 != NULL && c2 != NULL) {
      // いらないジャンプの削除
      if (c1->get_tag(0) == "jmp" && c1->get_tag(1) == c2->get_tag(0) && c2->is_label()) {
        codes[i] = NULL;
        codes[i+1] = NULL;
      }
    }
  }
}