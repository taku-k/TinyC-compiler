#include "codegen.hpp"
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

CodeGen::CodeGen(TC::Token_Driver *td) : token_driver(td), label(0) {
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
  c = "\tsub\tesp, " + IntToString(-(fn->get_count()));
  emit_code(c);

  // top_allocを進ませる
  // up_top_alloc

  // 関数本体のコード
  state_list_gen((StatList *)(((ComStatNode *)(fn->getnode(3)))->get_list(1)));
  c = "Lret_" + fn->getnode(1)->getname() + "\tmov\tesp, ebp";
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
          expr_gen((ExpressionList *)(n->getnode(0)));
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
    expr_gen((ExpressionList *)(isn->getnode(0)));

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
    expr_gen((ExpressionList *)(isn->getnode(0)));

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
  expr_gen((ExpressionList *)(wsn->getnode(0)));

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

void CodeGen::ret_state_gen(RETURNStatNode *rsn) {
  string c;
  // 式の計算コード生成
  expr_gen((ExpressionList *)(rsn->getnode(0)));

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

void CodeGen::expr_gen(ExpressionList *epl) {
  string c = "EXPR_GEN";
  emit_code(c);
}

// void CodeGen::emit_label() {
// }

void CodeGen::debug() {
  for (int i = 0; i < code.size(); i++) {
    cerr << code[i] << endl;
  }
}