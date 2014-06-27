#include "ast.hpp"

// NodeList methods
NodeList::~NodeList(void) {}

void NodeList::PrintTree(void) {
  std::cout << "---start---" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    std::cout << "(";
    list[i]->PrintNode();
    std::cout << ")\n";
  }
  std::cout << "\n---end---" << std::endl;
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
// NodeList end



// Nnode methods 
Nnode::Nnode() : op_(0), name_(""), value_(0), node_() {}




int Nnode::getop(void) {
  return op_;
}

int Nnode::getvalue(void) {
  return value_;
}

std::string Nnode::getname(void) {
  return name_;
}

Nnode *Nnode::getnode(int num) {
  if (num >=0 && num < N) {
    return node_[num];
  }
  return NULL;
}
// Nnode end





/* IdentifierNode
 * 識別子ノード
 */
IdentifierNode::IdentifierNode(std::string *id) {
  op_ = OP::ID;
  name_ = *id;
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
IntegerNode::IntegerNode(int val) : Nnode() {
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
DeclTypeNode::DeclTypeNode(const int op, Nnode* node) {
  op_ = op;
  node_[0] = node;
}

void DeclTypeNode::PrintNode(void) {
  node_[0]->PrintNode();
}
/*
 * DeclTypeNode END
 */


/* DeclList
 * 
 */
DeclList::DeclList(const int op, Nnode* list) {
  op_ = op;
  node_[1] = list;
}

DeclList::DeclList(const int op, Nnode* node, Nnode* list) {
  op_ = op;
  node_[0] = node;
  node_[1] = list;
}

DeclList::DeclList(Nnode* node, Nnode* list) {
  node_[0] = node;
  node_[1] = list;
}


void DeclList::PrintNode(void) {
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
  if (node_[0] != NULL) {
    node_[0]->PrintNode(op_);
  }
}
/*
 * END
 */

/* 
 * DeclNode
 */
DeclNode::DeclNode(std::string *id, TC::TC_Driver *d) {
  d->AddId(name_);
}

DeclNode::DeclNode(Nnode *node) {
  node_[0] = node;
}


void DeclNode::PrintNode(const int op) {
  switch(op){
    case(OP::INT):
      std::cout << "(int ";
  }
  PrintNum(0);
  std::cout << ") ";
}

void DeclNode::PrintNode(void) {
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
  std::cout << " ";
}
/*
 * END
 */


 /*
 * FuncNode 
 * 関数ノード
 */
FuncNode::FuncNode(Nnode* ret, Nnode* id, 
                    Nnode* paramlist, Nnode* stat) {
  op_ = OP::FUNC;
  node_[0] = ret;
  node_[1] = id;
  node_[2] = paramlist;
  node_[3] = stat;
}

void FuncNode::PrintNode(void) {
  std::cout << "( ";
  PrintNum(0);
  std::cout << " ";
  PrintNum(1);
  std::cout << ") (";
  PrintNum(2);
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


/* ParamDeclList
 * 
 */
ParamDeclList::ParamDeclList(Nnode* node, Nnode* list) {
  node_[0] = node;
  node_[1] = list;
}

void ParamDeclList::PrintNode(void) {
  PrintNum(1);
  PrintNum(0);
}
/*
 * ParamDeclList END
 */


/*
 * ParamDeclNode
 */
ParamDeclNode::ParamDeclNode(const int op, Nnode* node) {
  op_ = op;
  node_[0] = node;
}

void ParamDeclNode::PrintNode(void) {
  // DeclNodeでintも表示してもらう
  node_[0]->PrintNode(op_);
}
/*
 * ParamDeclNode END
 */


/*
 * ComStatNode { (first)int a,b; | (second)if(a>b)...}
 */
ComStatNode::ComStatNode(Nnode* first, Nnode* second) {
  node_[0] = first;
  node_[1] = second;
}

void ComStatNode::PrintNode(void) {
  std::cout << "{" << std::endl;
  // declartion
  PrintNum(0);
  // statement
  PrintNum(1);
  std::cout << "\n}";
}
/*
 * ComStatNode END
 */


/*
 * DeclarationList
 * node_[0] = DeclTypeNode, node_[1] = DeclarationList
 */
DeclarationList::DeclarationList(Nnode* node, Nnode* list) {
  node_[0] = node;
  node_[1] = list;
}

void DeclarationList::PrintNode() {
  node_[0]->PrintNode();
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
}

/*
 * DeclarationNode END
 */


/*
 * StatList
 */
StatList::StatList(Nnode* node, Nnode* list) {
  node_[0] = node;
  node_[1] = list;
}

void StatList::PrintNode(void) {
  PrintNum(1);
  PrintNum(0);
}
/*
 * StatList END
 */

/*
 * StatNode
 * node_[0] = 
 */
StatNode::StatNode(Nnode* node) {
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
ExpressionList::ExpressionList(Nnode* node, Nnode* list) {
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
IFStatNode::IFStatNode(Nnode* expr, Nnode* stat) {
  node_[0] = expr;
  node_[1] = stat;
}

IFStatNode::IFStatNode(Nnode* expr, Nnode* stat, Nnode* elsestat) {
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
WHILEStatNode::WHILEStatNode(Nnode* expr, Nnode* stat) {
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
RETURNStatNode::RETURNStatNode(Nnode* expr) {
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
AssignExprNode::AssignExprNode(Nnode *node) {
  node_[1] = node;
}

AssignExprNode::AssignExprNode(Nnode *id, Nnode* node) {
  node_[0] = id;
  node_[1] = node;
}


void AssignExprNode::PrintNode(void) {
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
ExprNode::ExprNode(const int op, Nnode *n1, Nnode *n2) {
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
      std::cout << "(/ ";
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
UnaryNode::UnaryNode(const int op, Nnode *node) : Nnode() {
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
FuncCallNode::FuncCallNode(Nnode *id, Nnode *args) : Nnode() {
  node_[0] = id;
  node_[1] = args;
}

void FuncCallNode::PrintNode(void) {
  std::cout << "(FCALL ";
  PrintNum(0);
  std::cout << " ";
  PrintNum(1);
  std::cout << ")";
}
/*
 * FuncCallNode END
 */


/*
 * FuncArgsNode
 */
FuncArgsNode::FuncArgsNode(Nnode *node, Nnode *list) : Nnode() {
  node_[0] = node;
  node_[1] = list;
}

void FuncArgsNode::PrintNode(void) {
  PrintNum(1);
  if (node_[0] != NULL) {
    PrintNum(0);
    std::cout << " ";
  }
}
