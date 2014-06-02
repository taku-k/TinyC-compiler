#include "node.hpp"

N-node::N-node(int op, std::string str) {
	op_ = op;
	name_ = str;
	value_ = 0;
	for (int i = 0; i < N-node::N; i++) {
		node_[i] = NULL;
	}
}

N-node::N-node(int op, int val) {
	op_ = op;
	name_ = NULL;
	value_ = val;
	for (int i = 0; i < N-node::N; i++) {
		node_[i] = NULL;
	}
}

N-node::N-node(int op, N-node *a) {
	op_ = op;
	name_ = NULL;
	value_ = 0;
	node_[0] = a;
	for (int i = 1; i < N-node::N; i++) {
		node_[i] = NULL;
	}
}	