#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class NodeList;
class Nnode;


// ノードのリスト
// 最も外部のノードを保持しておく
class NodeList{
public:
	NodeList(void) {}
	~NodeList(void);

	void add(Nnode *node) {
		list.push_back(node);
	}

	void PrintNode(void);

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

	static Nnode* MakeNode(int op, std::string str="", int val=0,
          Nnode *a=NULL, Nnode *b=NULL, Nnode *c=NULL, Nnode *d=NULL);
  static Nnode* MakeStat();
  static Nnode* MakeFuncDecl();
  static Nnode* MakeIfStat();
  static Nnode* MakeWhileStat();
  static Nnode* MakeElseStat();
  static Nnode* MakeRetStat();
  static Nnode* MakeIntDecl();

private:
	int op_;
	std::string name_;
	int value_;
	Nnode *node_[N];
};

