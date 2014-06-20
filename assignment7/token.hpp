#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <string>
#include <deque>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"

namespace TC{

class TkInfo {
public:
  enum {
    FRESH, VAR, FUN, PARM, UNDEFFUN
  };

  TkInfo(int lev, std::string str, int kind = FRESH)
        : op_(-1), lev_(lev), kind_(kind), offset_(-1), id_(str)
        , func_args_num(-1), relative_pos(-1) {};

  int get_op();
  int get_lev();
  int get_kind();
  int get_offset();
  std::string get_id();
  int get_func_args_num() {return func_args_num;};

  void set_kind(int i) {kind_ = i;}
  void set_lev(int i) {lev_ = i;}
  void set_func_args_num(int i) {func_args_num = i;}

  void debug();

private:
  int op_;
  int lev_;
  int kind_;
  int offset_;
  std::string id_;
  int func_args_num;
  int relative_pos;
};




class Token_Driver {
public:

  Token_Driver();
  ~Token_Driver();

  void Push(TkInfo *ti);
  void Pop(int lev);

  void level_up(){level_++;}
  void level_down(){level_--;}
  int get_cur_level(){return level_;}

  void debug();

  // idtable内で引数と同じシンボルがあればそのTkInfoのアドレスを返す
  // なければNULLを返す
  TC::TkInfo *lookup_sym(std::string id);
  void globalize_sym(TkInfo *ti);



private:
  std::deque<TkInfo *> idlist;

  std::deque<TkInfo *> debuglist;
  int level_;
};

}

#endif