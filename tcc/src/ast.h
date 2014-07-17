#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <string.h>
#include <deque>
#include <cstdio>
#include <stdarg.h>

#include "tc_driver.h"
#include "token.h"

class NodeList;
class Node;
class List;
class TkInfo;
namespace TC{
  class TC_Driver;
  class TC_Scanner;
}
class IdentifierNode;
class FuncCallNode;

namespace OP{
  enum {
    FUNC, FUNCNODE, STATNODE, COMSTATNODE, IFSTATNODE, IFELSESTATNODE,WHILESTATNODE, RETNODE,INT, ID, OR, AND, EQUAL, NOTEQUAL, LESSEQUAL,
     GREATEREQUAL, LESS, GREATER, ADD, SUB, MUL, DIV, MINUS, INTEGERNODE, DECLTYPENODE, RETSTATNODE, INTEGER, FUNCCALL, EXPRESSION,
     UNARY, BITOR, BITXOR, BITAND, ADDASSIGN, SUBASSIGN, FORSTATNODE, ASSIGN, POSTINC, POSTDEC, PREINC, PREDEC, 
  };
}


static TC::TC_Driver *tc_driver;
static TC::TC_Scanner *tc_scanner;
static TC::Token_Driver *token_driver;


// tc_driverにset
void set_tc_driver(TC::TC_Driver *d);

// tc_scannerにset
void set_tc_scanner(TC::TC_Scanner *s);

// token_driverにset
void set_token_driver(TC::Token_Driver *d);

// idnameと同じ変数名をtokenで探してあればそのトークン情報を持つノードを生成する
// なければ初期値のトークン情報を持つノードを生成する 
Node *make_identifier(std::string idname);

// nodeの持つトークン情報を解析して適宜変更、もしくは新しいトークンを生成する
Node *make_func_def(Node *node);
Node *ref_var(Node *node);
Node *ref_func(Node *node);




// ノードのリスト
// 最も外部のノードを保持しておく
class NodeList{
public:
  NodeList(TC::TC_Driver *d) : tcd(d) {}
  ~NodeList(void);

  void add(Node *node);

  void add(Node *node, TC::TC_Driver *d);

  void PrintTree(std::ostream &os);

  Node *get_node(int i) {return list[i];}

  int get_size() {return list.size();}

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

  // opを返す
  int getop(void);

  // valueを返す
  int getvalue(void);

  int get_type(void);

  // nameを返す
  std::string getname(void);

  // numで指定されたnodeを返す
  Node *getnode(int num);

  // nodeを表示する
  virtual void PrintNode(std::ostream &os) {}
  virtual void PrintNode(int, std::ostream &os) {}

  inline void PrintNum(int i, std::ostream &os) {
    if (node_[i] != NULL) {
      node_[i]->PrintNode(os);
    }
  }

  inline void debuglevel(){
  }

protected:
  int op_;
  int type_;
  std::string name_;
  int value_;
  Node *node_[N];
};


// リスト
class List {
public:
  List() {}
  virtual ~List(){};

  // nodeをelemsの末尾に挿入する
  virtual void append(Node *node) {
    elems.push_back(node);
  }

  // elemsの要素一つずつにPrintNodeを呼び出していく
  virtual void PrintList(std::ostream &os) {
    for (int i = 0; i < elems.size(); i++) {
      if (elems[i] != NULL) {
        elems[i]->PrintNode(os);
      }
    }
  }
  virtual void PrintList(int op, std::ostream &os){};

  // iで指定されたnodeを返す
  Node *get_elems_node(int i) { return elems[i]; }
  // elemsのサイズを返す
  int get_elems_size() { return elems.size(); }

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
  enum {
    DECL, REF
  };
  IdentifierNode(std::string id);
  IdentifierNode(std::string id, TC::TkInfo *tkinfo);
  ~IdentifierNode();

  TC::TkInfo *get_token_info();
  void set_token_info(TC::TkInfo *ti);

  void PrintNode(std::ostream &os);

  int get_offset_from_node();
private:
  TC::TkInfo *tkinfo_;
};

class IntegerNode : public Node {
public:
  IntegerNode(int val);
  void PrintNode(std::ostream &os);
private:
};


class DeclTypeNode : public Node {
public:
  DeclTypeNode(const int op, List* list);
  DeclTypeNode(const int op, List* list, TC::TC_Driver *d);
  void PrintNode(std::ostream &os);
  List *getlist() { return list_; }
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
  // node_[0] = RetNode, node_[1] = , node_[2] = ParamDeclList
  // node_[3] = ComStatNode
  FuncNode(Node* ret, Node* id, List* list, Node* stat);
  void PrintNode(std::ostream &os);
  int get_count() {return top_alloc;}
private:
  int top_alloc;
  List *list_;
};



class RetNode : public Node {
public:
  RetNode(const int op);
  void PrintNode(std::ostream &os);
private:
};


class ParamDeclNode : public Node {
public:
  ParamDeclNode(const int op, Node* node);
  void PrintNode(std::ostream &os);
private:
};

// compound_statement(bison)
class ComStatNode : public Node {
public:
  // list_[0] = DeclList, list_[1] = StatList
  // ComStatNode(Node* first, Node* second);
  ComStatNode(List *list1, List* list2);
  void PrintNode(std::ostream &os);
  // このノードの構文木の表示をすべて終えたらこの関数を実行して局所変数の開放を行う
  void all_relese();
  List *get_list(int i) {return list_[i];}
private:
  List *list_[2];
};


// statement(bison)
class StatNode : public Node {
public:
  // node_[0] = 
  StatNode(Node* node);
  void PrintNode(std::ostream &os);
private:
};



class IFStatNode : public Node {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  IFStatNode(Node* expr, Node* stat);
  IFStatNode(Node* expr, Node* stat, Node* elsestat);
  void PrintNode(std::ostream &os);
private:
};

class WHILEStatNode : public Node {
public:
  // node_[0] = ExpressionList, node_[1] = StatNode etc
  WHILEStatNode(Node* expr, Node* stat);
  void PrintNode(std::ostream &os);
private:
};

class RETURNStatNode : public Node {
public:
  // node_[0] = ExpressionList
  RETURNStatNode(Node* expr);
  void PrintNode(std::ostream &os);
private:
};

class FORStatNode : public Node {
public:
  FORStatNode(Node* ex1, Node* ex2, Node* ex3, Node* stat);
  void PrintNode(std::ostream &os);
private:
};


class AssignExprNode : public Node {
public:
  AssignExprNode(Node *node);
  AssignExprNode(int op, Node *id, Node* node);
  void PrintNode(std::ostream &os);
private:
};



// このクラスはlogical, equalty, relational, alithimeticを管理する
class ExprNode : public Node {
public:
  ExprNode(const int op, Node *n1, Node *n2);
  void PrintNode(std::ostream &os);
private:
};

class UnaryNode : public Node {
public:
  // node_[0] = 
  UnaryNode(const int op, Node *node);
  void PrintNode(std::ostream &os);
private:
};


class FuncCallNode : public Node {
public:
  // [0] = IdentifierNode, list_ = FuncArgsList
  FuncCallNode(Node *id, List *args);
  void PrintNode(std::ostream &os);
  List *getlist();
private:
  List *list_;
};


// expression(bison)
class ExpressionList : public Node {
public:
  // node_[0] = AssignExprNode, node_[1] = ExpressionList
  ExpressionList(Node* node, Node* list);
  void PrintNode(std::ostream &os);
private:
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
  void PrintList(int op, std::ostream &os);
};

class ParamDeclList : public List {
public:
  ParamDeclList() {}
  void append(Node *node);
  void set_param(ParamDeclList *l);
private:
};

class DeclarationList : public List {
public:
  DeclarationList() : count_(0) {}
  void PrintList(std::ostream &os);
  int set_all_offset();
  int get_count() { return count_; }
private:
  int count_;
};

class StatList : public List {
public:
  StatList() {}
private:
};

class FuncArgsList : public List {
public:
  FuncArgsList() {}
  void PrintList(std::ostream &os);
private:
};



#endif
