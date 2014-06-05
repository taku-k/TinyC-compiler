#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class NodeList;
class Nnode;

namespace OP{
  enum {
    FUNC, INT, ID,
  };
}

// ノードのリスト
// 最も外部のノードを保持しておく
class NodeList{
public:
	NodeList(void) {}
	~NodeList(void);

	void add(Nnode *node) {
		list.push_back(node);
	}

	void PrintTree(void);

  // debug 
  void Debug(void);

private:
	std::vector<Nnode*> list;
  // struct delete_object {
  //   void operator()(Nnode *ptr){ delete ptr; }
  // } ;
};



// ノード
class Nnode{
public:
	const static int N = 4;

  // constructor
  Nnode(void);
  Nnode(int op, std::string str);
  Nnode(int op, int val);
  Nnode(int op, Nnode *a);
  Nnode(int op, Nnode *a, Nnode *b);
  Nnode(int op, Nnode *a, Nnode *b, Nnode *c);
  Nnode(int op, Nnode *a, Nnode *b, Nnode *c, Nnode *d);

  // deconstructor
  virtual ~Nnode(void) {
    delete node_[0];
    delete node_[1];
    delete node_[2];
    delete node_[3];
  }

	int getop(void);
	int getvalue(void);
	std::string getname(void);
	Nnode *getnode(int num);

  virtual void PrintNode(void){};

	static Nnode* MakeNode(int op, std::string str="", int val=0,
          Nnode *a=NULL, Nnode *b=NULL, Nnode *c=NULL, Nnode *d=NULL);
  // static Nnode* MakeStat();
  // static Nnode* MakeFuncDecl();
  // static Nnode* MakeIfStat();
  // static Nnode* MakeWhileStat();
  // static Nnode* MakeElseStat();
  // static Nnode* MakeRetStat();
  // static Nnode* MakeIntDeclList();
  // static Nnode* MakeIntDecl();

protected:
	int op_;
	std::string name_;
	int value_;
	Nnode *node_[N];
};


class FuncNode : public Nnode {
public:
  FuncNode(Nnode* ret, Nnode* id, Nnode* paramlist, Nnode* stat);

  void PrintNode(void);
private:
};

class RetNode : public Nnode {
public:
  RetNode(std::string ret) {
    name_ = ret;
    if (ret == "INT") op_ = OP::INT;
  }
  void PrintNode(void) {
    std::cout << name_;
  }
private:
};

class IdentifierNode : public Nnode {
public:
  IdentifierNode(std::string id) {
    op_ = OP::ID;
    name_ = id;
  }
  void PrintNode(void) {
    std::cout << name_;
  }
private:
};


class DeclIntListNode : public Nnode {
public:
  // node_[0] には　nodeがつまりはIdが入る
  // node_[1] には後ろに続くリストが入る
  DeclIntListNode(int op, Nnode* node) {
    op_ = op;
    node_[1] = node;
  }
  DeclIntListNode(int op, Nnode* node, Nnode* list) {
    op_ = op;
    node_[0] = node;
    node_[1] = list;
  }
  void PrintNode(void) {
    if (node_[1] != NULL && node_[0] != NULL) {
      node_[0]->PrintNode();
      node_[1]->PrintNode();
    } else if (node_[0] == NULL) {
      node_[1]->PrintNode();
    }
  }
private:
};

class DeclIntNode : public Nnode {
public:
  DeclIntNode(std::string *id) {
    
  }
  void PrintNode(void) {
    std::cout << "(int " << name_ << ") ";
  }
private:
};

class ParamListNode : public Nnode {
public:

private:
  std::vector<Nnode*> list;
};

