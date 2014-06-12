#include <iostream>
#include <fstream>
#include <cstdlib>

#include "tc_driver.hpp"

TC::TC_Driver::~TC_Driver(){
	delete(scanner);
	scanner = NULL;
	delete(parser);
	parser = NULL;
}

void TC::TC_Driver::parse(const char *filename) {
	// 入力用のファイルストリーム
	std::ifstream in(filename);
	if (!in.good()) {
		std::cout << "Faild open such file\n";
		exit(EXIT_FAILURE);
	}

	// scannerの初期化
	delete(scanner);
	try {
		scanner = new TC::TC_Scanner(&in, *this);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild scanner" << std::endl;
		exit(EXIT_FAILURE);
	}

	// parserの初期化
	delete(parser);
	try {
		parser = new TC::TC_Parser( *scanner, *this);
	} catch (std::bad_alloc &ba) {
		std::cerr << "Faild parser" << std::endl;
		exit(EXIT_FAILURE);
	}

	// パースを開始する
	// const int accept(0);
	// if (parser->parse() != accept) {
	// 	std::cerr << "Parse failed" << std::endl;
	// }
	parser->parse();
}

void TC::TC_Driver::error(const std::string &err_m) {
	std::cerr << "Error: " << err_m << std::endl;
}
