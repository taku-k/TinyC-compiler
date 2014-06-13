#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <string>
#include <vector>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"

namespace TC{

class TkInfo {
public:
  enum {
    FRESH, VAR, FUN, PARM, UNDEFFU
  };

  TkInfo(int lev, std::string str) :
        op_(-1), lev_(lev), kind_(FRESH), offset_(-1), id_(str) {};

  int get_op();
  int get_lev();
  int get_kind();
  int get_offset();

  void debug();

private:
  int op_;
  int lev_;
  int kind_;
  int offset_;
  std::string id_;
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
  std::vector<TkInfo *> t_vec;
  int level_;
  std::vector<std::string> idtable;
};

}

#endif