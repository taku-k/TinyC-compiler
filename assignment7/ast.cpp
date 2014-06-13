#include "ast.hpp"

//
//                  NodeList methods
//
NodeList::~NodeList(void) {
	//std::for_each(list.begin(), list.end(), delete_object());
}

void NodeList::PrintTree(void) {
  std::cout << "---start---" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    std::cout << "(";
    list[i]->PrintNode();
    std::cout << ")\n";
  }
  std::cout << "---end---" << std::endl;
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
IdentifierNode::IdentifierNode(std::string *id, TC::TC_Driver *d) {
  op_ = OP::ID;
  name_ = *id;
  tkinfo_ = new TC::TkInfo((d->getTokenDriver())->get_level(), name_);
  (d->getTokenDriver())->Push(tkinfo_);
}

void IdentifierNode::PrintNode(void) {
  std::cout << name_;
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

void IntegerNode::PrintNode(void) {
  std::cout << value_;
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

void DeclTypeNode::PrintNode(void) {
  list_->PrintList(op_);
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
}

void FuncNode::PrintNode(void) {
  std::cout << "( ";
  PrintNum(0);
  std::cout << " ";
  PrintNum(1);
  std::cout << ") (";
  list_->PrintList();
  std::cout << ")\n";
  PrintNum(3);
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

void RetNode::PrintNode(void) {
  switch(op_) {
    case(OP::INT):
      std::cout << "int";
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

void ParamDeclNode::PrintNode(void) {
  // DeclNodeでintも表示してもらう
  switch(op_){
    case(OP::INT):
      std::cout << "(int ";
  }
  PrintNum(0);
  std::cout << ")";
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

void ComStatNode::PrintNode(void) {
  std::cout << "{" << std::endl;
  // declartion
  list_[0]->PrintList();
  // statement
  list_[1]->PrintList();
  std::cout << "}";
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

void StatNode::PrintNode(void) {
  PrintNum(0);
  std::cout << std::endl;
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

void ExpressionList::PrintNode(void) {
  PrintNum(1);
  if (node_[0] != NULL) {
    std::cout << "(";
    node_[0]->PrintNode();
    std::cout << ")";
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

void IFStatNode::PrintNode(void) {
  std::cout << "(IF ";
  PrintNum(0);
  std::cout << std::endl;
  PrintNum(1);
  if (node_[2] != NULL) {
    std::cout << " ELSE ";
    node_[2]->PrintNode();
    std::cout << ")\n"; 
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

void WHILEStatNode::PrintNode(void) {
  std::cout << "(WHILE ";
  PrintNum(0);
  std::cout << std::endl;
  PrintNum(1);
  std::cout << ")\n";
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

void RETURNStatNode::PrintNode(void) {
  std::cout << "(RETURN ";
  PrintNum(0);
  std::cout << " )";
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


void AssignExprNode::PrintNode(void) {
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
    std::cout << "(= ";
    node_[0]->PrintNode();
    std::cout << " ";
    PrintNum(1);
    std::cout << ")";
  } else {
    PrintNum(1);
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

void ExprNode::PrintNode(void) {
  switch(op_) {
    case(OP::OR):
      std::cout << "(|| ";
      break;
    case(OP::AND):
      std::cout << "(&& ";
      break;
    case(OP::GREATEREQUAL):
      std::cout << "(>= ";
      break;
    case(OP::LESSEQUAL):
      std::cout << "(<= ";
      break;
    case(OP::EQUAL):
      std::cout << "(== ";
      break;
    case(OP::NOTEQUAL):
      std::cout << "(!= ";
      break;
    case(OP::LESS):
      std::cout << "(< ";
      break;
    case(OP::GREATER):
      std::cout << "(> ";
      break;
    case(OP::ADD):
      std::cout << "(+ ";
      break;
    case(OP::SUB):
      std::cout << "(- ";
      break;
    case(OP::MUL):
      std::cout << "(* ";
      break;
    case(OP::DIV):
      std::cout << "/ ";
      break;
  }
  PrintNum(0);
  std::cout << " ";
  PrintNum(1);
  std::cout << ")";
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

void UnaryNode::PrintNode(void) {
  switch(op_) {
    case(OP::MINUS):
      std::cout << "(- ";
      break;
  }
  PrintNum(0);
  std::cout << ")";
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

void FuncCallNode::PrintNode(void) {
  std::cout << "(FCALL ";
  PrintNum(0);
  std::cout << " ";
  list_->PrintList();
  std::cout << ")";
}
/*
 * FuncCallNode END
 */





void DeclList::PrintList(int op) {
  op_ = op;
  for (int i = 0; i < elems.size(); i++) {
    if (elems[i] != NULL) {
      switch(op_){
        case(OP::INT):
          std::cout << "(int ";
      }
      elems[i]->PrintNode();
      std::cout << ")";
    }
  }
}


void FuncArgsList::PrintList() {
  for (int i = 0; i < elems.size(); i++) {
    elems[i]->PrintNode();
    std::cout << " ";
  }
}