#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <string>
#include <deque>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "ast.hpp"

class FuncCallNode;

namespace TC{

class TkInfo {
public:
  enum {
    FRESH, VAR, FUN, PARM, UNDEFFUN, DECL, REF
  };

  TkInfo(int lev, std::string str, int kind = FRESH)
        : op_(-1), lev_(lev), kind_(kind), offset_(-1), id_(str)
        , func_args_num(-1) {};

  int get_op();
  int get_lev();
  int get_kind();
  int get_offset();
  std::string get_id();
  int get_func_args_num() {return func_args_num;};

  void set_op(int i)            { op_ = i;            }
  void set_kind(int i)          { kind_ = i;         }
  void set_lev(int i)           { lev_ = i;          }
  void set_func_args_num(int i) { func_args_num = i; }
  void set_offset(int i)        { offset_ = i;       }

  void debug();

private:
  int op_;
  int lev_;
  int kind_;
  int offset_;
  std::string id_;
  int func_args_num;
};




class Token_Driver {
public:

  Token_Driver();
  ~Token_Driver();

  // idlistとtotal_listの操作関数
  void Push(TkInfo *ti);
  void Pop(int lev);
  std::deque<TkInfo *> get_id_list() { return idlist; }

  // level関係の関数
  void level_up(){level_++;}
  void level_down(){level_--;}
  int get_cur_level(){return level_;}

  // idlistのデバッグ関数 
  void debug();

  // idtable内で引数と同じシンボルがあればそのTkInfoのアドレスを返す
  // なければNULLを返す
  TC::TkInfo *lookup_sym(std::string id);
  void globalize_sym(TkInfo *ti);

  // 相対番地関係の関数
  int allocate_loc();
  void release_loc(int cnt);


  // 関数呼び出し関連の関数
  void add_func_call_node(std::string id, int args_size);
  std::vector<std::pair<std::string, int > > get_func_call_list() { return func_call_list; }

private:
  std::deque<TkInfo *> idlist;

  std::deque<TkInfo *> total_list;

  std::vector<std::pair<std::string, int> > func_call_list;

  int level_;
  int last_alloc;
  int top_alloc;
};

}

#endif