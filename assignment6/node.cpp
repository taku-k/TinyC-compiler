#include "node.hpp"

// NodeList methods
NodeList::~NodeList(void) {
	//std::for_each(list.begin(), list.end(), delete_object());
}

void NodeList::PrintTree(void) {
  std::cout << "---start---" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    std::cout << "(";
    list[i]->PrintNode();
    std::cout << ")";
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
Nnode::Nnode(void) {
  op_ = 0;
  name_ = "";
  value_ = 0;
  for (int i = 0; i < Nnode::N; i++) {
    node_[i] = NULL;
  }
}
Nnode::Nnode(const int op, std::string str) {
	op_ = op;
	name_ = str;
	value_ = 0;
	for (int i = 0; i < Nnode::N; i++) {
		node_[i] = NULL;
	}
}

Nnode::Nnode(const int op, int val) {
	op_ = op;
	name_ = "";
	value_ = val;
	for (int i = 0; i < Nnode::N; i++) {
		node_[i] = NULL;
	}
}

Nnode::Nnode(const int op, Nnode *a) {
	op_ = op;
	name_ = "";
	value_ = 0;
	node_[0] = a;
  node_[1] = NULL;
  node_[2] = NULL;
  node_[3] = NULL;
}

Nnode::Nnode(const int op, Nnode *a, Nnode *b) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = NULL;
  node_[3] = NULL;
}

Nnode::Nnode(const int op, Nnode *a, Nnode *b, Nnode *c) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = c;
  node_[3] = NULL;
}

Nnode::Nnode(const int op, Nnode *a, Nnode *b, Nnode *c, Nnode *d) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = c;
  node_[3] = d;
}

Nnode* Nnode::MakeNode(const int op, std::string str, int val, Nnode *a /* NULL */,
        Nnode *b /* NULL */, Nnode *c /* NULL */, Nnode *d /* NULL */) {
  if (d != NULL) {
    return new Nnode(op, a, b, c, d);
  } else if (c != NULL) {
    return new Nnode(op, a, b, c);
  } else if (b != NULL) {
    return new Nnode(op, a, b);
  } else if (a != NULL) {
    return new Nnode(op, a);
  } else if (val == 0) {
    return new Nnode(op, str);
  } else if (str == "") {
    return new Nnode(op, val);
  } else {
    /*
     * error
     */

  }
  return NULL;
}


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
IdentifierNode::IdentifierNode(std::string id) {
  op_ = OP::ID;
  name_ = id;
}

void IdentifierNode::PrintNode(void) {
  std::cout << name_;
}
/*
 * END
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
  // if (node_[1] != NULL && node_[0] != NULL) {
  //   node_[0]->PrintDecl(op_);
  //   node_[1]->PrintNode();
  // } else if (node_[0] != NULL) {
  //   node_[0]->PrintDecl(op_);
  // } else if (node_[0] == NULL) {
  //   node_[1]->PrintNode();
  // }
  node_[0]->PrintNode(op_);
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
}
/*
 * END
 */

/* 
 * DeclNode
 */
DeclNode::DeclNode(std::string *id) {
  name_ = *id;
}

void DeclNode::PrintNode(const int op) {
  switch(op){
    case(OP::INT):
      std::cout << "(int " << name_ << ") ";
    default:
      return;
  }
  return;
}

void DeclNode::PrintNode(void) {
  std::cout << name_ << " ";
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
  node_[0]->PrintNode();
  std::cout << " ";
  node_[1]->PrintNode();
  std::cout << ") (";
  if (node_[2] != NULL) {
    node_[2]->PrintNode();
  }
  std::cout << ")\n";
  if (node_[3] != NULL) {
    node_[3]->PrintNode();
  }
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
  node_[0]->PrintNode();
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
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
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
  // statement
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
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

// void DeclarationList::PrintNode(void) {
//   node_[0]->PrintNode();
//   if(node_[1] != NULL) {
//     node_[1]->PrintNode();
//   }
// }
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
  node_[0]->PrintNode();
  if(node_[1] != NULL) {
    node_[1]->PrintNode();
  }
}
/*
 * StatList END
 */

/*
 * StatNode
 * node_[0] = 
 */
StatNode::StatNode(Nnode * node) {
  node_[0] = node;
}

void StatNode::PrintNode(void) {
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
}
/*
 * StatNode END
 */


/*
 * ExpressionNode
 */
ExpressionNode::ExpressionNode(Nnode *node) {
  node_[0] = node;
}

void ExpressionNode::PrintNode(void) {

}
/*
 * ExpressionNode END
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
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
  std::cout << std::endl;
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
  if (node_[2] != NULL) {
    std::cout << "ELSE {\n";
    node_[2]->PrintNode();
    std::cout << "\n}"; 
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
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
  std::cout << std::endl;
  if (node_[1] != NULL) {
    node_[1]->PrintNode();
  }
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
  if (node_[0] != NULL) {
    node_[0]->PrintNode();
  }
}
/*
 * RETURNStatNode END
 */