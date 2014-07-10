#include "codegen.h"
#include <sstream>




// intをstringに変換する関数
string IntToString(int number)
{
  stringstream ss;
  ss << number;
  return ss.str();
}



// void TC::Token_Driver::release_loc(int cnt = 0) {
//   if (cnt != 0) {
//     last_alloc += (4 * cnt);
//   } else {
//     last_alloc += 4;
//   }
// }

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
    emit_code("\tCOMMON\t" + id->getname() + "\t" + IntToString(4));
  }
}

void CodeGen::func_decl_gen(FuncNode *fn) {
  // top_allocセット
  final_temp_alloc = top_alloc = -(fn->get_count());

  // returnラベルの生成
  ret_label = "Lret_" + fn->getnode(1)->getname();

  // fnのnode_[1] = IdentiferNode
  emit_code("\tGLOBAL\t" + fn->getnode(1)->getname());
  emit_code(fn->getnode(1)->getname() + ":");
  emit_code("\tpush\tebp");
  emit_code("\tmov\tebp,esp");

  // 挿入位置をマークしておく
  emit_code("TEMP_ALLOC_CODE");

  // top_allocを進ませる
  // up_top_alloc

  // 関数本体のコード
  state_list_gen((StatList *)(((ComStatNode *)(fn->getnode(3)))->get_list(1)));

  emit_code(ret_label + ":");
  emit_code("\tmov\tesp,ebp");
  emit_code("\tpop\tebp");
  emit_code("\tret");

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

    emit_code("\tcmp\teax,0");
    emit_code("\tje\t" + L1);
    //本体コードの生成
    state_gen(isn->getnode(1));
    emit_code(L1 + ":");

  } else {
    // else節が存在するならば 
    L2 = make_label();
    // 条件式コードの生成 結果が偽ならばL1へジャンプ
    expr_list_gen((ExpressionList *)(isn->getnode(0)));

    emit_code("\tcmp\teax,0");
    emit_code("\tje\t" + L1);
    // if節のコード生成
    state_gen(isn->getnode(1));
    emit_code("\tjmp\t" + L2);
    emit_code(L1 + ":");
    // else節のコード生成
    state_gen(isn->getnode(2));
    emit_code(L2 + ":");
  }
}

void CodeGen::while_state_gen(WHILEStatNode *wsn) {
  string s = make_label();
  string e = make_label();

  emit_code(s + ":");
  // 条件式コード生成
  expr_list_gen((ExpressionList *)(wsn->getnode(0)));

  emit_code("\tcmp\teax,0");
  emit_code("\tje\t" + e);
  // 本体のコード生成
  state_gen(wsn->getnode(1));

  emit_code("\tjmp\t" + s);
  emit_code(e + ":");

}


void CodeGen::ret_state_gen(RETURNStatNode *rsn) {
  // 式の計算コード生成
  expr_list_gen((ExpressionList *)(rsn->getnode(0)));

  emit_code("\tjmp\t" + ret_label);
}



void CodeGen::expr_list_gen(ExpressionList *epl) {
  assign_expr_gen((AssignExprNode *)(epl->getnode(0)));
  if (epl->getnode(1) != NULL) {
    expr_list_gen((ExpressionList *)(epl->getnode(1)));
  }
}

void CodeGen::assign_expr_gen(AssignExprNode *aen) {
  string c;
  // 左辺に変数をもつ場合
  if (aen->getnode(0) != NULL) {
    // 右辺の実行
    assign_expr_gen((AssignExprNode *)(aen->getnode(1)));
    // 指定の番地に値を戻す
    IdentifierNode *n = (IdentifierNode *)(aen->getnode(0));

    // 大域変数の場合
    if (n->get_token_info()->get_lev() == 0) {
      emit_code("\tmov\t[" + n->getname() + "],eax");
    } else {
      c = "\tmov\t[ebp";
      if (n->get_offset_from_node() > 0) {
        c += "+";
      }
      c += IntToString(n->get_offset_from_node()) + "],eax";
      emit_code(c);
    }
  } else {
    expr_gen(aen->getnode(1));
  }
}

void CodeGen::expr_gen(Node *n) {
  string c, label;
  IdentifierNode *in;
  int op = n->getop();
  int tmp;
  switch(op) {

    case OP::ADD:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tadd\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;


    case OP::SUB:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tsub\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;


    case OP::MUL:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\timul\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;


    case OP::DIV:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcdq");
      emit_code("\tidiv\tdword [ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;

    case OP::BITOR:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tor\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;

    case OP::BITXOR:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\txor\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;

    case OP::BITAND:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tand\teax,[ebp-" + IntToString(tmp) + "]");
      release_temp();
      break;

    case OP::GREATEREQUAL:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsetge\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;


    case OP::LESSEQUAL:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsetle\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;

    case OP::EQUAL:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsete\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;


    case OP::NOTEQUAL:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsetne\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;


    case OP::LESS:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsetl\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;


    case OP::GREATER:
      expr_gen(n->getnode(1));
      emit_code("\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "],eax");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,[ebp-" + IntToString(tmp) + "]");
      emit_code("\tsetg\tal");
      emit_code("\tmovzx\teax,al");
      release_temp();
      break;


    case OP::OR:
      label = make_label();
      emit_code("\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "],0");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,0");
      emit_code("\tje\t" + label);
      expr_gen(n->getnode(1));
      emit_code("\tcmp\teax,0");
      emit_code("\tje\t" + label);
      emit_code("\tmov\tdword [ebp-" + IntToString(tmp) + "],1");
      emit_code(label + ":");
      emit_code("\tmov\teax,[ebp-" + IntToString(tmp) + "]");
      break;

    case OP::AND:
      label = make_label();
      emit_code("\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "],1");
      expr_gen(n->getnode(0));
      emit_code("\tcmp\teax,0");
      emit_code("\tjne\t" + label);
      expr_gen(n->getnode(1));
      emit_code("\tcmp\teax,0");
      emit_code("\tjne\t" + label);
      emit_code("\tmov\tdword [ebp-" + IntToString(tmp) + "],0");
      emit_code(label + ":");
      emit_code("\tmov\teax,[ebp-" + IntToString(tmp) + "]");
      break;

    case OP::ID:
      in = (IdentifierNode *)n;
      if (in->get_token_info()->get_lev() == 0) {
        emit_code("\tmov\teax, [" + in->getname() + "]");
      } else {
        c = "\tmov\teax, [ebp";
        if (in->get_offset_from_node() > 0) {
          c += "+";
        }
        c += IntToString(in->get_offset_from_node()) + "]";
        emit_code(c);
      }
      break;

    case OP::INTEGER:
      emit_code("\tmov\teax," + IntToString(n->getvalue()));
      break;

    case OP::FUNCCALL:
      func_call_gen((FuncCallNode *)n);
      break;

    case OP::UNARY:
      expr_gen(n->getnode(0));
      emit_code("\timul\teax, -1");
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
    emit_code("EXTERN\t" + id->getname());
  }

  // 引数をスタックに積んでいく.
  for (int i = args->get_elems_size()-1; i >= 0 ; i--) {
    assign_expr_gen( ( AssignExprNode * )(args->get_elems_node(i)) );
    emit_code("\tpush\teax");
  }
  emit_code("\tcall\t" + id->getname());
  // スタックポイントを戻しておく
  emit_code("\tadd\tesp," + IntToString(4 * args->get_elems_size()));
}




// コード出力関係
void CodeGen::emit_code(string c) {
  code.push_back(c);
}

string CodeGen::make_label() {
  string ret = "L" + IntToString(label++);
  return ret;
}

void CodeGen::release_code() {
  // 出力する前に最適化を行う
  optimize_code();
  for (int i = 0; i < code.size(); i++) {
    (*out) << code[i] << endl;
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
  for (int i = code.size() - 1; i >= 0; i--) {
    if (code[i] == "TEMP_ALLOC_CODE") {
      code[i] = "\tsub\tesp," + IntToString(final_temp_alloc);
    }
  }
}

void CodeGen::optimize_code() {
  for (int i = 0; i < code.size(); i++) {

  }
}