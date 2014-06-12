#ifndef __TCDRIVER_HPP__
#define __TCDRIVER_HPP__

#include <string>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"

namespace TC{

class TC_Driver {
public:

	TC_Driver() : parser(NULL),scanner(NULL),nodel(NULL){};
	virtual ~TC_Driver();

  // パース関数
	void parse(const char *filename);

  // エラーを出力する関数
  void error(const std::string &err_m);

  // 構文木を出力する関数 
  void print();

  void debug();

  void AddId(std::string id);

private:
  TC::TC_Parser *parser;
  TC::TC_Scanner *scanner;
  NodeList *nodel;

  std::vector<std::string> idtable;
};

}

#endif