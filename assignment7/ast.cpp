#include "ast.hpp"



void set_tc_driver(TC::TC_Driver *d) {
  tc_driver = d;
}
void set_tc_scanner(TC::TC_Scanner *s) {
  tc_scanner = s;
}

void set_token_driver(TC::Token_Driver *d) {
  token_driver = d;
}


// idを引数にしてその名前と同じノードがすでに宣言されていたら
// そのノードのトークン情報を使って新しいノードを作成
// なければ初期値のノードを作成
Node *make_identifier(std::string idname) {
  if (token_driver->lookup_sym(idname)) {
    // std::cerr << token_driver->lookup_sym(idname) << std::endl;
    return new IdentifierNode(idname,token_driver->lookup_sym(idname));
  }
  return new IdentifierNode(idname);
}

Node *make_func_def(Node *node) {
  IdentifierNode *n = (IdentifierNode *)node;
  TC::TkInfo *ti = n->get_token_info();
  switch (ti->get_kind()) {
    case (TC::TkInfo::VAR):
      tc_driver->error("`%s` redeclared as different kind of symbol", ti->get_id().c_str());
      break;
    case (TC::TkInfo::FUN):
      tc_driver->error("redefinition of `%s`", ti->get_id().c_str());
      break;
    case (TC::TkInfo::UNDEFFUN):
    case (TC::TkInfo::FRESH):
      ti->set_kind(TC::TkInfo::FUN);
      break;
  }
  return node;
}

Node *ref_var(Node *node) {
  IdentifierNode *n = (IdentifierNode *)node;
  TC::TkInfo *ti = n->get_token_info();
  switch (ti->get_kind()) {
    case (TC::TkInfo::VAR):
    case (TC::TkInfo::PARM):
      break;
    case (TC::TkInfo::FUN):
    case (TC::TkInfo::UNDEFFUN):
      tc_driver->error("function `%s` is used as variable", n->getname().c_str());
      break;
    case (TC::TkInfo::FRESH):
      tc_driver->error("`%s` undeclared variable", n->getname().c_str());
      ti->set_kind(TC::TkInfo::VAR);
      break;
  }
  return node;
}

Node *ref_func(Node *node) {
  IdentifierNode *n = (IdentifierNode *)node;
  TC::TkInfo *ti = n->get_token_info();
  switch (ti->get_kind()) {
    case (TC::TkInfo::VAR):
    case (TC::TkInfo::PARM):
      tc_driver->error("variable `%s` is used as function", n->getname().c_str());
      break;
    case (TC::TkInfo::FUN):
    case (TC::TkInfo::UNDEFFUN):
      break;
    case (TC::TkInfo::FRESH):
      tc_driver->warn("`%s` undeclared function", n->getname().c_str());
      ti->set_kind(TC::TkInfo::UNDEFFUN);
      if (ti->get_lev() > 0) {
        ti->set_lev(0);
        token_driver->globalize_sym(ti);
      }
      break;
  }
  return node;
}







//
//                  NodeList methods
//
NodeList::~NodeList(void) {

}

void NodeList::add(Node *node) {
  list.push_back(node);
}

void NodeList::add(Node *node, TC::TC_Driver *d) {
  list.push_back(node);
  std::cout << tcd;
}

void NodeList::PrintTree(std::ostream &os) {
  os << "---start---" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    os << "(";
    list[i]->PrintNode(os);
    os << ")\n";
  }
  os << "---end---" << std::endl;
  // std::cout << "Driver : " << tc_driver 
  //       << "\nScanner: " << tc_scanner << std::endl;
}


void NodeList::Debug(void) {
  std::cout << "-----Debug start-----" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    std::cout << "Op: " << list[i]->getop() << std::endl;
    std::cout << "Value: " << list[i]->getvalue() << std::endl;
    std::cout << "Name: " << list[i]->getname() << std::endl;
  }
  std::cout << "------Debug end------" << std::endl;
}
//
//                    NodeList end
//



//
//                   Node methods
//
Node::Node() : op_(0), name_(""), value_(0), node_() {}

int Node::getop(void) {
  return op_;
}

int Node::getvalue(void) {
  return value_;
}

std::string Node::getname(void) {
  return name_;
}

Node *Node::getnode(int num) {
  if (num >=0 && num < N) {
    return node_[num];
  }
  return NULL;
}

//
//                       Node end
//




/* IdentifierNode
 * 識別子ノード
 */
// IdentifierNode::IdentifierNode(std::string *id) {
//   op_ = OP::ID;
//   name_ = *id;
//   tkinfo_ = new TC::TkInfo(token_driver->get_cur_level(), name_);
//   token_driver->Push(tkinfo_);
// }

IdentifierNode::IdentifierNode(std::string id) {
  op_ = OP::ID;
  name_ = id;
  tkinfo_ = new TC::TkInfo(token_driver->get_cur_level(), name_);
  token_driver->Push(tkinfo_);
}

IdentifierNode::IdentifierNode(std::string id, TC::TkInfo *tkinfo) {

  op_ = OP::ID;
  name_ = id;
  tkinfo_ = tkinfo;
}

TC::TkInfo *IdentifierNode::get_token_info() {
  return tkinfo_;
}

void IdentifierNode::set_token_info(TC::TkInfo *ti) {
  tkinfo_ = ti;
}

IdentifierNode::~IdentifierNode() {
  delete tkinfo_;
}

void IdentifierNode::PrintNode(std::ostream &os) {
  os << name_;
}
/*
 * END
 */


/*
 * IntegerNode
 */
IntegerNode::IntegerNode(int val) : Node() {
  value_ = val;
}

void IntegerNode::PrintNode(std::ostream &os) {
  os << value_;
}
/*
 * IntegerNode END
 */



/* 
 * DeclTypeNode
 */
DeclTypeNode::DeclTypeNode(const int op, List* list) {
  op_ = op;
  list_ = list;
}

DeclTypeNode::DeclTypeNode(const int op, List* list, TC::TC_Driver *d) {
  op_ = op;
  list_ = list;
  // std::cout << (d->getTokenDriver())->get_level() << std::endl;
}

void DeclTypeNode::PrintNode(std::ostream &os) {
  list_->PrintList(op_, os);
}
/*
 * DeclTypeNode END
 */



// /* 
//  * DeclNode
//  */
// // この時にTokenInfoを作成する。
// DeclNode::DeclNode(Node *id, TC::TC_Driver *d) {
//   node_[0] = id;
//   //std::cout << (d->getTokenDriver())->get_level() << std::endl;
// }

// DeclNode::DeclNode(Node *node) {
//   node_[0] = node;
// }


// void DeclNode::PrintNode(const int op) {
//   switch(op){
//     case(OP::INT):
//       std::cout << "(int ";
//   }
//   PrintNum(0);
//   std::cout << ") ";
// }

// void DeclNode::PrintNode(void) {
//   if (node_[0] != NULL) {
//     node_[0]->PrintNode();
//   }
//   std::cout << " ";
// }
// /*
//  * END
//  */


 /*
 * FuncNode 
 * 関数ノード
 */
FuncNode::FuncNode(Node* ret, Node* id, 
                    List* list, Node* stat) {
  op_ = OP::FUNC;
  node_[0] = ret;
  node_[1] = id;
  list_ = list;
  node_[3] = stat;

  ((ParamDeclList *)list_)->set_param((ParamDeclList *)list_);
}

void FuncNode::PrintNode(std::ostream &os) {
  os << "( ";
  PrintNum(0, os);
  os << " ";
  PrintNum(1, os);
  os << ") (";
  list_->PrintList(os);
  os << ")\n";
  PrintNum(3, os);
}
/*
 *  FundNode END
 */


/* RetNode
 * 返り値ノード
 */
RetNode::RetNode(const int op) {
  op_ = op;
}

void RetNode::PrintNode(std::ostream &os) {
  switch(op_) {
    case(OP::INT):
      os << "int";
  }
}
/*
 * RetNode END
 */




/*
 * ParamDeclNode
 */
ParamDeclNode::ParamDeclNode(const int op, Node* node) {
  op_ = op;
  node_[0] = node;
}

void ParamDeclNode::PrintNode(std::ostream &os) {
  // DeclNodeでintも表示してもらう
  switch(op_){
    case(OP::INT):
      os << "(int ";
  }
  PrintNum(0, os);
  os << ")";
}
/*
 * ParamDeclNode END
 */


/*
 * ComStatNode { (first)int a,b; | (second)if(a>b)...}
 */

ComStatNode::ComStatNode(List* list1, List* list2) {
  list_[0] = list1;
  list_[1] = list2;
}

void ComStatNode::PrintNode(std::ostream &os) {
  os << "{" << std::endl;
  // declartion
  list_[0]->PrintList(os);
  // statement
  list_[1]->PrintList(os);
  os << "}";
}
/*
 * ComStatNode END
 */



/*
 * StatNode
 * node_[0] = 
 */
StatNode::StatNode(Node* node) {
  node_[0] = node;
}

void StatNode::PrintNode(std::ostream &os) {
  PrintNum(0, os);
  os << std::endl;
}
/*
 * StatNode END
 */


/*
 * ExpressionList
 * node_[0] = AssignExprNode, node_[1] = ExpressionList
 */
ExpressionList::ExpressionList(Node* node, Node* list) {
  node_[0] = node;
  node_[1] = list;
}

void ExpressionList::PrintNode(std::ostream &os) {
  PrintNum(1, os);
  if (node_[0] != NULL) {
    os << "(";
    node_[0]->PrintNode(os);
    os << ")";
  }
}
/*
 * ExpressionList END
 */


/*
 * IFStatNode
 */
IFStatNode::IFStatNode(Node* expr, Node* stat) {
  node_[0] = expr;
  node_[1] = stat;
}

IFStatNode::IFStatNode(Node* expr, Node* stat, Node* elsestat) {
  node_[0] = expr;
  node_[1] = stat;
  node_[2] = elsestat;
}

void IFStatNode::PrintNode(std::ostream &os) {
  os << "(IF ";
  PrintNum(0, os);
  os << std::endl;
  PrintNum(1, os);
  if (node_[2] != NULL) {
    os << " ELSE ";
    node_[2]->PrintNode(os);
    os << ")\n"; 
  }
}
/*
 * IFStatNode END
 */

/*
 * WHILEStatNode
 */
WHILEStatNode::WHILEStatNode(Node* expr, Node* stat) {
  node_[0] = expr;
  node_[1] = stat;
}

void WHILEStatNode::PrintNode(std::ostream &os) {
  os << "(WHILE ";
  PrintNum(0, os);
  os << std::endl;
  PrintNum(1, os);
  os << ")\n";
}
/*
 * WHILEStatNode END
 */


/*
 * RETURNStatNode
 */
RETURNStatNode::RETURNStatNode(Node* expr) {
  node_[0] = expr;
}

void RETURNStatNode::PrintNode(std::ostream &os) {
  os << "(RETURN ";
  PrintNum(0, os);
  os << " )";
}
/*
 * RETURNStatNode END
 */


/*
 * AssignExprNode 
 */
AssignExprNode::AssignExprNode(Node *node) {
  node_[1] = node;
}

AssignExprNode::AssignExprNode(Node *id, Node* node) {
  node_[0] = id;
  node_[1] = node;
}


void AssignExprNode::PrintNode(std::ostream &os) {
  // if (node_[0] != NULL) {
  //   if (name_ == "") {
  //     node_[0]->PrintNode();
  //   } else {
  //     std::cout << "(= " << name_ << " ";
  //     node_[0]->PrintNode();
  //     std::cout << ")";
  //   }
  // }
  if (node_[0] != NULL) {
    os << "(= ";
    node_[0]->PrintNode(os);
    os << " ";
    PrintNum(1, os);
    os << ")";
  } else {
    PrintNum(1, os);
  }
}
/*
 * AssignExprNode END
 */

/*
 * ExprNode
 */
ExprNode::ExprNode(const int op, Node *n1, Node *n2) {
  op_ = op;
  node_[0] = n1;
  node_[1] = n2;
}

void ExprNode::PrintNode(std::ostream &os) {
  switch(op_) {
    case(OP::OR):
      os << "(|| ";
      break;
    case(OP::AND):
      os << "(&& ";
      break;
    case(OP::GREATEREQUAL):
      os << "(>= ";
      break;
    case(OP::LESSEQUAL):
      os << "(<= ";
      break;
    case(OP::EQUAL):
      os << "(== ";
      break;
    case(OP::NOTEQUAL):
      os << "(!= ";
      break;
    case(OP::LESS):
      os << "(< ";
      break;
    case(OP::GREATER):
      os << "(> ";
      break;
    case(OP::ADD):
      os << "(+ ";
      break;
    case(OP::SUB):
      os << "(- ";
      break;
    case(OP::MUL):
      os << "(* ";
      break;
    case(OP::DIV):
      os << "/ ";
      break;
  }
  PrintNum(0, os);
  os << " ";
  PrintNum(1, os);
  os << ")";
}
/*
 * ExprNode END
 */

/*
 * UnaryNode
 */
UnaryNode::UnaryNode(const int op, Node *node) : Node() {
  op_ = op;
  node_[0] = node;
}

void UnaryNode::PrintNode(std::ostream &os) {
  switch(op_) {
    case(OP::MINUS):
      os << "(- ";
      break;
  }
  PrintNum(0, os);
  os << ")";
}
/*
 * UnaryNode END
 */

/*
 * FuncCallNode
 */
FuncCallNode::FuncCallNode(Node *id, List *args) : Node() {
  node_[0] = id;
  list_ = args;
}



void FuncCallNode::PrintNode(std::ostream &os) {
  os << "(FCALL ";
  PrintNum(0, os);
  os << " ";
  list_->PrintList(os);
  os << ")";
}
/*
 * FuncCallNode END
 */


/*
 *                DeclList
 *                nodeにはIdentifierNode
 */
void DeclList::append(Node *node) {
  IdentifierNode *n = (IdentifierNode *)node;
  TC::TkInfo *ti = n->get_token_info();
  switch (ti->get_kind()) {

    case (TC::TkInfo::VAR):
      // 同一レベルであれば二重宣言でエラー
      if (ti->get_lev() == token_driver->get_cur_level()) {
        tc_driver->error("redeclaration of `%s`", ti->get_id().c_str());
      }
      // 新しくtkinfoを生成して、検索対象に追加する
      n->set_token_info(new TC::TkInfo(token_driver->get_cur_level(), ti->get_id()));
      token_driver->Push(n->get_token_info());
      break;

    case (TC::TkInfo::FUN):       // すでに関数として宣言されているか
    case (TC::TkInfo::UNDEFFUN):  // すでに未定義関数として名前が使用されている
      // 同一レベルであれば二重宣言
      if (ti->get_lev() == token_driver->get_cur_level()) {
        tc_driver->error("`%S` redeclaration as different kind of symbol", ti->get_id().c_str());
      }
      // 新しくtkinfoを生成して、検索対象に追加する
      n->set_token_info(new TC::TkInfo(token_driver->get_cur_level(), ti->get_id()));
      token_driver->Push(n->get_token_info());
      break;

    case (TC::TkInfo::PARM):
      tc_driver->warn("declaration of `%s` shadows a parameter", ti->get_id().c_str());
      // 新しくtkinfoを生成して、検索対象に追加する
      n->set_token_info(new TC::TkInfo(token_driver->get_cur_level(), ti->get_id()));
      token_driver->Push(n->get_token_info());
      break;

    case (TC::TkInfo::FRESH):
      break;
  }
  ti = n->get_token_info();
  ti->set_kind(TC::TkInfo::VAR);
  // ti->set_lev(token_driver->get_cur_level());
  // 最後にdequeに格納
  elems.push_back((Node *)n);
}


void DeclList::PrintList(int op, std::ostream &os) {
  op_ = op;
  for (int i = 0; i < elems.size(); i++) {
    if (elems[i] != NULL) {
      switch(op_){
        case(OP::INT):
          os << "(int ";
      }
      elems[i]->PrintNode(os);
      os << ")";
    }
  }
}
/*
 *                DeclList
 */


/*
 *                ParamDeclList
 */
void ParamDeclList::append(Node *node) {
  // NodeをIdentifierNodeにキャストする
  IdentifierNode *n = (IdentifierNode *)(node->getnode(0));
  TC::TkInfo *ti = n->get_token_info();

  switch (ti->get_kind()) {
    case (TC::TkInfo::VAR):
    case (TC::TkInfo::FUN):
    case (TC::TkInfo::UNDEFFUN):
      n->set_token_info(new TC::TkInfo(token_driver->get_cur_level(), ti->get_id()));
      token_driver->Push(n->get_token_info());
      break;

    case (TC::TkInfo::PARM):
      tc_driver->error("redeclaration of `%s`", ti->get_id().c_str());
      elems.push_back((Node *)node);
      return;

    case (TC::TkInfo::FRESH):
      break;

  }
  ti = n->get_token_info();
  ti->set_kind(TC::TkInfo::PARM);
  elems.push_back((Node *)node);
}

// パラメータは8,12,16,...の順にoffsetをセットする
void ParamDeclList::set_param(ParamDeclList *l) {
  std::deque<Node *> e = l->elems;
  for (int i = 0; i < e.size(); i++) {
    IdentifierNode *n = (IdentifierNode *)(e[i]->getnode(0));
    TC::TkInfo *ti = n->get_token_info();
    ti->set_offset(4*(i+2));
  }
}

void FuncArgsList::PrintList(std::ostream &os) {
  for (int i = 0; i < elems.size(); i++) {
    elems[i]->PrintNode(os);
    os << " ";
  }
}