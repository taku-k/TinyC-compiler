#include <iostream>
#include <fstream>

#include "tc_driver.hpp"

TC::TC_Driver::~TC_Driver(){
	delete(scanner);
	scanner = nullptr;
	delete(parser);
	parser = nullptr;
}

void TC::TC_Driver::parse() {
	delete(scanner);
	try {
		scanner = new TC::TC_Scanner(&std::cin);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild" << std::endl;
		exit(EXIT_FAILURE);
	}

	delete(parser);
	try {
		parser = new TC::TC_Parser( *scanner, *this);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild" << std::endl;
		exit(EXIT_FAILURE);
	}

	const int accept(0);
	if (parser->parse() != accept) {
		std::cerr << "Parse failed" << std::endl;
	}
}
