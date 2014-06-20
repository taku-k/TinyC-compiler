#ifndef __TCDRIVER_HPP__
#define __TCDRIVER_HPP__

#include <string>
#include <deque>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"
#include "token.hpp"

namespace TC{

// class Token_Driver;
// class TkInfo;

class TC_Driver {
public:

	TC_Driver() : parser(NULL),scanner(NULL),nodel(NULL),
            t_driver(NULL), semnerrs(0) {};
	virtual ~TC_Driver();

  // パース関数
	void parse(const char *filename);

  // エラーを出力する関数
  void error(const std::string &err_m);

  // 構文木を出力する関数 
  void print();

  TC::Token_Driver *getTokenDriver() { 
    return t_driver;
  }

  int get_semnerrs() { return semnerrs; }

  void semnerrs_up() {
    semnerrs++;
  }

private:
  TC::TC_Parser *parser;
  TC::TC_Scanner *scanner;
  NodeList *nodel;
  TC::Token_Driver *t_driver;

  int semnerrs;
};





}

#endif