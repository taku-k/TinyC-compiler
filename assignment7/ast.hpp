#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <string.h>

#include "tc_driver.hpp"

class NodeList;
class Nnode;

namespace OP{
  enum {
    FUNC, INT, ID, OR, AND, EQUAL, NOTEQUAL, LESSEQUAL,
     GREATEREQUAL, LESS, GREATER, ADD, SUB, MUL, DIV, MINUS
  };
}

// ノードのリスト
// 最も外部のノードを保持しておく
class NodeList{
public:
	NodeList() {}
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

  static const int N = 4;

  // constructor
  Nnode();
  // Nnode(const int op, std::string str);
  // Nnode(const int op, int val);
  // Nnode(const int op, Nnode *a);
  // Nnode(const int op, Nnode *a, Nnode *b);
  // Nnode(const int op, Nnode *a, Nnode *b, Nnode *c);
  // Nnode(const int op, Nnode *a, Nnode *b, Nnode *c, Nnode *d);

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
  virtual void PrintNode(int) {}

  inline void PrintNum(int i) {
    if (node_[i] != NULL) {
      node_[i]->PrintNode();
    }
  }
  // virtual void PrintDecl(int) {}
  // virtual void PrintDecl(void) {}

  // static Nnode* MakeNode(const int op, std::string str="", int val=0,
 //          Nnode *a=NULL, Nnode *b=NULL, Nnode *c=NULL, Nnode *d=NULL);
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
  IdentifierNode(std::string *id);
  void PrintNode(void);
private:
};

class IntegerNode : public Nnode {
public:
  IntegerNode(int val);
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
  // node_[0] = DeclNode, node_[1] = DeclList
  DeclList(const int op, Nnode* list);
  DeclList(const int op, Nnode* node, Nnode* list);
  DeclList(Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

class DeclNode : public Nnode {
public:
  DeclNode(Nnode *node);
  DeclNode(std::string *id, TC::TC_Driver *d);
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
  // node_[0] = ParamDeclNode, node_[1] = ParamDeclList
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
class ExpressionList : public Nnode {
public:
  // node_[0] = AssignExprNode, node_[1] = ExpressionList
  ExpressionList(Nnode* node, Nnode* list);
  void PrintNode(void);
private:
};

class IFStatNode : public Nnode {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  IFStatNode(Nnode* expr, Nnode* stat);
  IFStatNode(Nnode* expr, Nnode* stat, Nnode* elsestat);
  void PrintNode(void);
private:
};

class WHILEStatNode : public Nnode {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  WHILEStatNode(Nnode* expr, Nnode* stat);
  void PrintNode(void);
private:
};

class RETURNStatNode : public Nnode {
public:
  // node_[0] = ExpressionList
  RETURNStatNode(Nnode* expr);
  void PrintNode(void);
private:
};


class AssignExprNode : public Nnode {
public:
  AssignExprNode(Nnode *node);
  AssignExprNode(Nnode *id, Nnode* node);
  void PrintNode(void);
private:
};

// このクラスはlogical, equalty, relational, alithimeticを管理する
class ExprNode : public Nnode {
public:
  ExprNode(const int op, Nnode *n1, Nnode *n2);
  void PrintNode(void);
private:
};

class UnaryNode : public Nnode {
public:
  // node_[0] = 
  UnaryNode(const int op, Nnode *node);
  void PrintNode(void);
private:
};

class FuncCallNode : public Nnode {
public:
  FuncCallNode(Nnode *id, Nnode *args);
  void PrintNode(void);
private:
};

class FuncArgsNode : public Nnode {
public:
  FuncArgsNode(Nnode *node, Nnode *list);
  void PrintNode(void);
private:
};



#endif
