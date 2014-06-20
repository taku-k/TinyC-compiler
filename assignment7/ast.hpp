#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <string.h>
#include <deque>
#include <cstdio>
#include <stdarg.h>

#include "tc_driver.hpp"
#include "token.hpp"

class NodeList;
class Node;
class List;
class TkInfo;
namespace TC{
  class TC_Driver;
  class TC_Scanner;
}
class IdentifierNode;

namespace OP{
  enum {
    FUNC, INT, ID, OR, AND, EQUAL, NOTEQUAL, LESSEQUAL,
     GREATEREQUAL, LESS, GREATER, ADD, SUB, MUL, DIV, MINUS
  };
}


static TC::TC_Driver *tc_driver;
static TC::TC_Scanner *tc_scanner;
static TC::Token_Driver *token_driver;
void set_tc_driver(TC::TC_Driver *d);
void set_tc_scanner(TC::TC_Scanner *s);
void set_token_driver(TC::Token_Driver *d);

Node *make_identifier(std::string idname);
Node *make_func_def(Node *node);
Node *ref_var(Node *node);
Node *ref_func(Node *node);

void error(const char *fmt, ...);
void warn(const char *fmt, ...);


// ノードのリスト
// 最も外部のノードを保持しておく
class NodeList{
public:
  NodeList(TC::TC_Driver *d) : tcd(d) {}
  ~NodeList(void);

  void add(Node *node);

  void add(Node *node, TC::TC_Driver *d);

  void PrintTree(void);

  // debug 
  void Debug(void);

private:
  std::vector<Node*> list;
  TC::TC_Driver *tcd;
};



// 
//            基底クラスの宣言
//              List, Node
//

// ノード
class Node{
public:

  static const int N = 4;

  // constructor
  Node();
  // Node(List*, Node*);

  // deconstructor
  virtual ~Node(void) {
    delete node_[0];
    delete node_[1];
    delete node_[2];
    delete node_[3];
  }

  int getop(void);
  int getvalue(void);
  std::string getname(void);
  Node *getnode(int num);

  virtual void PrintNode(void) {}
  virtual void PrintNode(int) {}

  inline void PrintNum(int i) {
    if (node_[i] != NULL) {
      node_[i]->PrintNode();
    }
  }

  inline void debuglevel(){
  }

protected:
  int op_;
  std::string name_;
  int value_;
  Node *node_[N];
};


// リスト
class List {
public:
  List() {}
  virtual ~List(){};

  virtual void append(Node *node) {
    elems.push_back(node);
  }

  virtual void PrintList(void) {
    for (int i = 0; i < elems.size(); i++) {
      if (elems[i] != NULL) {
        elems[i]->PrintNode();
      }
    }
  }
  virtual void PrintList(int){};

protected:
  std::deque<Node *> elems;
  int op_;
};

//
//                基底クラスここまで
//
//



//
//
//                Node から 継承
//
//


class IdentifierNode : public Node {
public:
  IdentifierNode(std::string id);
  IdentifierNode(std::string id, TC::TkInfo *tkinfo);
  ~IdentifierNode();
  TC::TkInfo *get_token_info();
  void set_token_info(TC::TkInfo *ti);
  void PrintNode(void);
private:
  TC::TkInfo *tkinfo_;
};

class IntegerNode : public Node {
public:
  IntegerNode(int val);
  void PrintNode(void);
private:
};


class DeclTypeNode : public Node {
public:
  DeclTypeNode(const int op, List* list);
  DeclTypeNode(const int op, List* list, TC::TC_Driver *d);
  void PrintNode(void);
private:
  List *list_;
};

// //
// //    宣言
// //    意味情報を持つ
// class DeclNode : public Node {
// public:
//   DeclNode(Node *node);
//   DeclNode(Node *id, TC::TC_Driver *d);
//   void PrintNode(const int op);
//   // ParamDeclNodeとの連携で"int"をどのタイミングで表示する？
//   void PrintNode(void);
// private:
//   TkInfo *tkinfo_;
// };
// //
// //



class FuncNode : public Node {
public:
  // node_[0] = RetNode, node_[1] = DeclNode, node_[2] = ParamDeclList
  // node_[3] = ComStatNode
  FuncNode(Node* ret, Node* id, List* list, Node* stat);
  void PrintNode(void);
private:
  List *list_;
};



class RetNode : public Node {
public:
  RetNode(const int op);
  void PrintNode(void);
private:
};


class ParamDeclNode : public Node {
public:
  ParamDeclNode(const int op, Node* node);
  void PrintNode(void);
private:
};

// compound_statement(bison)
class ComStatNode : public Node {
public:
  // node_[0] = DeclList, node_[1] = StatList
  // ComStatNode(Node* first, Node* second);
  ComStatNode(List *list1, List* list2);
  void PrintNode(void);
private:
  List *list_[2];
};


// statement(bison)
class StatNode : public Node {
public:
  // node_[0] = 
  StatNode(Node* node);
  void PrintNode(void);
private:
};

// expression(bison)
class ExpressionList : public Node {
public:
  // node_[0] = AssignExprNode, node_[1] = ExpressionList
  ExpressionList(Node* node, Node* list);
  void PrintNode(void);
private:
};

class IFStatNode : public Node {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  IFStatNode(Node* expr, Node* stat);
  IFStatNode(Node* expr, Node* stat, Node* elsestat);
  void PrintNode(void);
private:
};

class WHILEStatNode : public Node {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  WHILEStatNode(Node* expr, Node* stat);
  void PrintNode(void);
private:
};

class RETURNStatNode : public Node {
public:
  // node_[0] = ExpressionList
  RETURNStatNode(Node* expr);
  void PrintNode(void);
private:
};


class AssignExprNode : public Node {
public:
  AssignExprNode(Node *node);
  AssignExprNode(Node *id, Node* node);
  void PrintNode(void);
private:
};

// このクラスはlogical, equalty, relational, alithimeticを管理する
class ExprNode : public Node {
public:
  ExprNode(const int op, Node *n1, Node *n2);
  void PrintNode(void);
private:
};

class UnaryNode : public Node {
public:
  // node_[0] = 
  UnaryNode(const int op, Node *node);
  void PrintNode(void);
private:
};


class FuncCallNode : public Node {
public:
  FuncCallNode(Node *id, List *args);
  void PrintNode(void);
private:
  List *list_;
};


// 
//
//            List から 継承
//
//

class DeclList : public List {
public:
  DeclList() {}
  void append(Node *node);
  void PrintList(int op);
};

class ParamDeclList : public List {
public:
  ParamDeclList() {}
  void append(Node *node);
private:
};

class DeclarationList : public List {
public:
  DeclarationList() {}
private:
};

class StatList : public List {
public:
  StatList() {}
private:
};

class FuncArgsList : public List {
public:
  FuncArgsList() {}
  void PrintList();
private:
};

#endif
