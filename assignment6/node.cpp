#include "node.hpp"

// NodeList methods
NodeList::~NodeList(void) {
	//std::for_each(list.begin(), list.end(), delete_object());
}

void NodeList::PrintTree(void) {
  std::cout << "{" << std::endl;
  for (int i = 0; i < list.size(); i++) {
    std::cout << "(";
    list[i]->PrintNode();
    std::cout << ")";
  }
  std::cout << "\n}" << std::endl;
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
Nnode::Nnode(int op, std::string str) {
	op_ = op;
	name_ = str;
	value_ = 0;
	for (int i = 0; i < Nnode::N; i++) {
		node_[i] = NULL;
	}
}

Nnode::Nnode(int op, int val) {
	op_ = op;
	name_ = "";
	value_ = val;
	for (int i = 0; i < Nnode::N; i++) {
		node_[i] = NULL;
	}
}

Nnode::Nnode(int op, Nnode *a) {
	op_ = op;
	name_ = "";
	value_ = 0;
	node_[0] = a;
  node_[1] = NULL;
  node_[2] = NULL;
  node_[3] = NULL;
}

Nnode::Nnode(int op, Nnode *a, Nnode *b) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = NULL;
  node_[3] = NULL;
}

Nnode::Nnode(int op, Nnode *a, Nnode *b, Nnode *c) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = c;
  node_[3] = NULL;
}

Nnode::Nnode(int op, Nnode *a, Nnode *b, Nnode *c, Nnode *d) {
  op_ = op;
  name_ = "";
  value_ = 0;
  node_[0] = a;
  node_[1] = b;
  node_[2] = c;
  node_[3] = d;
}

Nnode* Nnode::MakeNode(int op, std::string str, int val, Nnode *a /* NULL */,
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
  std::cout << "((";
  node_[0]->PrintNode();
  std::cout << " ";
  node_[1]->PrintNode();
  std::cout << ") (";
  node_[2]->PrintNode();
  std::cout << ")\n(\n";
  node_[3]->PrintNode();
  std::cout << "))\n";
}
/*
 *  FundNode END
 */

