#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <string.h>

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
  Nnode(const int op, std::string str);
  Nnode(const int op, int val);
  Nnode(const int op, Nnode *a);
  Nnode(const int op, Nnode *a, Nnode *b);
  Nnode(const int op, Nnode *a, Nnode *b, Nnode *c);
  Nnode(const int op, Nnode *a, Nnode *b, Nnode *c, Nnode *d);

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

  virtual void PrintNode(void) {
    node_[0]->PrintNode();
    if (node_[1] != NULL) {
      node_[1]->PrintNode();
    }
  }
  virtual void PrintNode(int) {}
  // virtual void PrintDecl(int) {}
  // virtual void PrintDecl(void) {}

	static Nnode* MakeNode(const int op, std::string str="", int val=0,
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



class IdentifierNode : public Nnode {
public:
  IdentifierNode(std::string id);
  void PrintNode(void);
private:
};


class DeclTypeNode : public Nnode {
public:
  DeclTypeNode(const int op, Nnode* node);
  void PrintNode(void);
private:
};


class DeclList : public Nnode {
public:
  // node_[0] には　nodeがつまりはIdが入る
  // node_[1] には後ろに続くリストが入る
  DeclList(const int op, Nnode* list);
  DeclList(const int op, Nnode* node, Nnode* list);
  DeclList(Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

class DeclNode : public Nnode {
public:
  DeclNode(std::string *id);
  void PrintNode(const int op);
  // ParamDeclNodeとの連携で"int"をどのタイミングで表示する？
  void PrintNode(void);
private:
};

class FuncNode : public Nnode {
public:
  // node_[0] = RetNode, node_[1] = DeclNode, node_[2] = ParamDeclList
  // node_[3] = ComStatNode
  FuncNode(Nnode* ret, Nnode* id, Nnode* paramlist, Nnode* stat);
  void PrintNode(void);
private:
};

class RetNode : public Nnode {
public:
  RetNode(const int op);
  void PrintNode(void);
private:
};


class ParamDeclList : public Nnode {
public:
  // 一つ目がノード
  ParamDeclList(Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

class ParamDeclNode : public Nnode {
public:
  // node_[0] = DeclNode
  ParamDeclNode(const int op, Nnode* node);
  void PrintNode(void);
private:
};

// compound_statement(bison)
class ComStatNode : public Nnode {
public:
  // node_[0] = DeclList, node_[1] = StatList
  ComStatNode(Nnode* first, Nnode* second);
  void PrintNode(void);
private:
};

class DeclarationList : public Nnode {
public:
  // node_[0] = DeclTypeNode, node_[1] = DeclarationList
  DeclarationList(Nnode* node, Nnode* list);
private:
};

class StatList : public Nnode {
public:
  // node_[0] = StatNode or IFStatNode or WHILEStatNode or 
  // node_[1] = StatList
  StatList(Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

// statement(bison)
class StatNode : public Nnode {
public:
  // node_[0] = 
  StatNode(Nnode* node);
  void PrintNode(void);
private:
};

// expression(bison)
class ExpressionNode : public Nnode {
public:
  ExpressionNode(Nnode* node);
  void PrintNode(void);
private:
};

class IFStatNode : public Nnode {
public:
  // node_[0] = 
  IFStatNode(Nnode* expr, Nnode* stat);
  IFStatNode(Nnode* expr, Nnode* stat, Nnode* elsestat);
  void PrintNode(void);
private:
};

class WHILEStatNode : public Nnode {
public:
  WHILEStatNode(Nnode* expr, Nnode* stat);
  void PrintNode(void);
private:
};

class RETURNStatNode : public Nnode {
public:
  RETURNStatNode(Nnode* expr);
  void PrintNode(void);
private:
};
