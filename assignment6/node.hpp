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

  virtual void PrintNode(void) {}
  virtual void PrintDecl(int) {}
  virtual void PrintDecl(void) {}

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



class IdentifierNode : public Nnode {
public:
  IdentifierNode(std::string id);
  void PrintNode(void);
private:
};


class DeclListNode : public Nnode {
public:
  // node_[0] には　nodeがつまりはIdが入る
  // node_[1] には後ろに続くリストが入る
  DeclListNode(int op, Nnode* list);
  DeclListNode(int op, Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

class DeclNode : public Nnode {
public:
  DeclNode(std::string *id);
  void PrintDecl(int op);
  // ParamDeclNodeとの連携で"int"をどのタイミングで表示する？
  void PrintDecl(void);
private:
};

class FuncNode : public Nnode {
public:
  FuncNode(Nnode* ret, Nnode* id, Nnode* paramlist, Nnode* stat);
  void PrintNode(void);
private:
};

class RetNode : public Nnode {
public:
  RetNode(int op);
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
  ParamDeclNode(int op, Nnode* node);
  void PrintNode(void);
private:
};

