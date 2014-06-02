#include <iostream>
#include <string>

class N-node{
public:
	const static int N = 4;

	// constructor
	N-node(int op, std::string str);
	N-node(int op, int val);
	N-node(int op, N-node *a);
	N-node(int op, N-node *a, N-node *b);
	N-node(int op, N-node *a, N-node *b, N-node *c);
	N-node(int op, N-node *a, N-node *b, N-node *c, N-node *d);

	// deconstructor
	virtual ~N-node() {
		delete node_[0];
		delete node_[1];
		delete node_[2];
		delete node_[3];
		delete name_;
	}

	int op();
	int value();
	std::string name();
	N-node *node(int num);


private:
	int op_;
	std::string name_;
	int value_;
	N-node *node_[N];
};