#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tc_driver.hpp"

TC::TC_Driver::~TC_Driver(){
  delete(scanner);
  scanner = NULL;
  delete(parser);
  parser = NULL;
  delete(nodel);
  nodel = NULL;
}

void TC::TC_Driver::parse(const char *filename) {
  // 入力用のファイルストリーム
  std::ifstream in(filename);
  if (!in.good()) {
    std::cout << "No such file\n";
    exit(EXIT_FAILURE);
  }

  delete(scanner);
  try {
    scanner = new TC::TC_Scanner(&in, *this);
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

  delete(t_driver);
  try {
    t_driver = new Token_Driver();
    // std::cout << this << std::endl;
  } catch (std::bad_alloc &ba) {
    std::cerr << "Faild TokenDriver" << std::endl;
    exit(EXIT_FAILURE);
  }

  delete(parser);
  try {
    parser = new TC::TC_Parser( *scanner, *this, *nodel);
  } catch (std::bad_alloc &ba) {
    std::cerr << "Faild: parser" << std::endl;
    exit(EXIT_FAILURE);
  }

  // パースを開始する
  parser->parse();
}

void TC::TC_Driver::error(const std::string &err_m) {
  std::cerr << "Error: " << err_m << std::endl;
}

void TC::TC_Driver::print() {
  nodel->PrintTree();
}



// Token_Driver
//
TC::Token_Driver::Token_Driver() {}

TC::Token_Driver::~Token_Driver() {}

void TC::Token_Driver::Push(TkInfo *ti) {
	t_stack.push_front(ti);
}

TC::TkInfo* TC::Token_Driver::Pop() {
	TC::TkInfo *ret = t_stack.front();
	t_stack.pop_front();
	return ret;
}

void TC::Token_Driver::add_id(std::string id) {
  idtable.push_back(id);
}

void TC::Token_Driver::debug() {
  for (int i = 0; i < idtable.size(); i++) {
    std::cout << idtable[i] << std::endl;
  }
}

