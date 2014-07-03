#include "codegen.h"
#include <sstream>


// intをstringに変換する関数
string IntToString(int number)
{
  stringstream ss;
  ss << number;
  return ss.str();
}

// int TC::Token_Driver::allocate_loc() {
//   last_alloc -= 4;
//   if (last_alloc < top_alloc) {
//     top_alloc = last_alloc;
//   }
//   return last_alloc;
// }

// void TC::Token_Driver::release_loc(int cnt = 0) {
//   if (cnt != 0) {
//     last_alloc += (4 * cnt);
//   } else {
//     last_alloc += 4;
//   }
// }

CodeGen::CodeGen(TC::Token_Driver *td) : label(0) {
}

void CodeGen::code_generate(NodeList *nl) {
  for (int i = 0; i < nl->get_size(); i++) {
    switch(nl->get_node(i)->get_type()) {
      case(OP::FUNCNODE):
        func_decl_gen((FuncNode*)(nl->get_node(i)));
        break;
      default:
        break;
    }
  }
}

void CodeGen::func_decl_gen(FuncNode *fn) {
  string c = "";
  // top_allocセット
  top_alloc = -(fn->get_count());
  // fnのnode_[1] = IdentiferNode
  c = "\tGLOBAL\t" + fn->getnode(1)->getname();
  emit_code(c);
  c = fn->getnode(1)->getname() + "\tpush\tebp";
  emit_code(c);
  c = "\tmov\tebp, esp";
  emit_code(c);

  // TODO: 一時変数分のスタック領域をあけるようにする
  c = "\tsub\tesp, " + IntToString(-(fn->get_count()));
  emit_code(c);

  // top_allocを進ませる
  // up_top_alloc

  // 関数本体のコード
  state_list_gen((StatList *)(((ComStatNode *)(fn->getnode(3)))->get_list(1)));

  // TODO: 関数のリターンラベル処理 （現在はLretのまま）
  // c = "Lret_" + fn->getnode(1)->getname() + "\tmov\tesp, ebp";
  c = "Lret\tmov\tesp, ebp";
  emit_code(c);
  c = "\tpop\tebp";
  emit_code(c);
  c = "\tret";
  emit_code(c);
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
  string c, L1, L2;
  L1 = make_label();
  if (isElse == false) {
    // else節が存在しないならば
    //条件式コードの生成 結果が偽ならばl1にジャンプ
    expr_list_gen((ExpressionList *)(isn->getnode(0)));

    c = "\tcmp\teax, 0";
    emit_code(c);
    c = "\tje\t" + L1;
    emit_code(c);
    //本体コードの生成
    state_gen(isn->getnode(1));

    emit_code(L1 + ":");
  } else {
    // else節が存在するならば 
    L2 = make_label();
    // 条件式コードの生成 結果が偽ならばL1へジャンプ
    expr_list_gen((ExpressionList *)(isn->getnode(0)));

    c = "\tcmp\teax, 0";
    emit_code(c);
    c = "\tje\t" + L1;
    emit_code(c);
    // if節のコード生成
    state_gen(isn->getnode(1));

    c = "\tjmp\t" + L2;
    emit_code(c);
    // else節のコード生成
    state_gen(isn->getnode(2));

    c = L1 + ":";
    emit_code(c);

    c = L2 + ":";
    emit_code(c);
  }
}

void CodeGen::while_state_gen(WHILEStatNode *wsn) {
  string c;
  string s = make_label();
  string e = make_label();

  // 条件式コード生成
  expr_list_gen((ExpressionList *)(wsn->getnode(0)));

  c = "\tcmp\teax, 0";
  emit_code(c);
  c = "\tje\t" + e;
  emit_code(c);
  // 本体のコード生成
  state_gen(wsn->getnode(1));

  c = "\tjmp\t" + s;
  emit_code(c);
  emit_code(e + ":");

}

// TODO: リターンラベルを組み込む
void CodeGen::ret_state_gen(RETURNStatNode *rsn) {
  string c;
  // 式の計算コード生成
  expr_list_gen((ExpressionList *)(rsn->getnode(0)));

  c = "\tjmp\tLret";
  emit_code(c);
}

void CodeGen::emit_code(string c) {
  code.push_back(c);
}

string CodeGen::make_label() {
  string ret = "L" + IntToString(label++);
  return ret;
}

void CodeGen::expr_list_gen(ExpressionList *epl) {
  string c;
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
    c = "\tmov\t[ebp";
    if (n->get_offset_from_node() > 0) {
      c += "+";
    }
    c += IntToString(n->get_offset_from_node()) + "], eax";
    emit_code(c);
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

    case(OP::ADD):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tadd\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      release_temp();
      break;


    case(OP::SUB):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tsub\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      release_temp();
      break;


    case(OP::MUL):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\timul\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      release_temp();
      break;


    case(OP::DIV):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcdq";
      emit_code(c);
      c = "\tidiv\tdword [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      release_temp();
      break;

    case(OP::GREATEREQUAL):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsetge\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;


    case(OP::LESSEQUAL):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsetle\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;

    case(OP::EQUAL):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsete\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;


    case(OP::NOTEQUAL):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsetne\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;


    case(OP::LESS):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsetl\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;


    case(OP::GREATER):
      expr_gen(n->getnode(1));
      c = "\tmov\t[ebp-" + IntToString(tmp=create_temp_alloc()) + "], eax";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      c = "\tsetg\tal";
      emit_code(c);
      c = "\tmovzx\teax, al";
      emit_code(c);
      release_temp();
      break;


    case(OP::OR):
      label = make_label();
      c = "\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "], 0";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, 0";
      emit_code(c);
      c = "\tje\t" + label;
      emit_code(c);
      expr_gen(n->getnode(1));
      c = "\tcmp\teax, 0";
      emit_code(c);
      c = "\tje\t" + label;
      emit_code(c);
      c = "\tmov\tdword [ebp-" + IntToString(tmp) + "], 1";
      emit_code(c);
      emit_code(label + ":");
      c = "\tmov\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      break;

    case(OP::AND):
      label = make_label();
      c = "\tmov\tdword [ebp-" + IntToString(tmp=create_temp_alloc()) + "], 1";
      emit_code(c);
      expr_gen(n->getnode(0));
      c = "\tcmp\teax, 0";
      emit_code(c);
      c = "\tjne\t" + label;
      emit_code(c);
      expr_gen(n->getnode(1));
      c = "\tcmp\teax, 0";
      emit_code(c);
      c = "\tjne\t" + label;
      emit_code(c);
      c = "\tmov\tdword [ebp-" + IntToString(tmp) + "], 0";
      emit_code(c);
      emit_code(label + ":");
      c = "\tmov\teax, [ebp-" + IntToString(tmp) + "]";
      emit_code(c);
      break;

    case(OP::ID):
      in = (IdentifierNode *)n;
      c = "\tmov\teax, [ebp";
      if (in->get_offset_from_node() > 0) {
        c += "+";
      }
      c += IntToString(in->get_offset_from_node()) + "]";
      emit_code(c);
      break;

    case(OP::INTEGER):
      c = "\tmov\teax, ";
      c += IntToString(n->getvalue());
      emit_code(c);
      break;
  }
}

// void CodeGen::emit_label() {
// }

void CodeGen::debug() {
  for (int i = 0; i < code.size(); i++) {
    cerr << code[i] << endl;
  }
}