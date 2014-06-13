#ifndef __TCDRIVER_HPP__
#define __TCDRIVER_HPP__

#include <string>
#include <deque>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"

namespace TC{

class Token_Driver;
class TkInfo;

class TC_Driver {
public:

	TC_Driver() : parser(NULL),scanner(NULL),nodel(NULL),t_driver(NULL) {};
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

private:
  TC::TC_Parser *parser;
  TC::TC_Scanner *scanner;
  NodeList *nodel;
  TC::Token_Driver *t_driver;
};



class TkInfo {
public:
  TkInfo(int op, int lev, int offset) :
        op_(op), lev_(lev), kind_(), offset_(offset) {};
private:
  int op_;
  int lev_;
  enum {FRESH, VAR, FUN, PARM, UNDEFFUN} kind_;
  int offset_;
};




class Token_Driver {
public:

  Token_Driver();
  ~Token_Driver();

  void Push(TkInfo *ti);
  TkInfo* Pop();

  void level_up(){level_++;}
  void level_down(){level_--;}
  int get_level(){return level_;}

  void add_id(std::string id);

  void debug();

private:
  std::deque<TkInfo *> t_stack;
  int level_;
  std::vector<std::string> idtable;
};

}

#endif