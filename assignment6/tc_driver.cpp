#include <iostream>
#include <fstream>

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