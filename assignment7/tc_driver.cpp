#include <iostream>
#include <fstream>
#include <vector>

#include "tc_driver.hpp"

TC::TC_Driver::~TC_Driver(){
	delete(scanner);
	scanner = NULL;
	delete(parser);
	parser = NULL;
	delete(nodel);
	nodel = NULL;
}

void TC::TC_Driver::parse() {
	delete(scanner);
	try {
		scanner = new TC::TC_Scanner(&std::cin);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild: scanner" << std::endl;
		exit(EXIT_FAILURE);
	}

	delete(nodel);
	try {
		nodel = new NodeList();
		// std::cout << this << std::endl;
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild nodelist" << std::endl;
		exit(EXIT_FAILURE);
	}

	delete(parser);
	try {
		parser = new TC::TC_Parser( *scanner, *this, *nodel);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild: parser" << std::endl;
		exit(EXIT_FAILURE);
	}

	const int accept(0);
	if (parser->parse() != accept) {
		std::cerr << "Parse failed" << std::endl;
	}
}

void TC::TC_Driver::print() {
	nodel->PrintTree();
}

void TC::TC_Driver::debug() {
	for (int i = 0; i < idtable.size(); i++) {
		std::cout << idtable[i] << std::endl;
	}
}

void TC::TC_Driver::AddId(std::string id) {
	idtable.push_back(id);
}
