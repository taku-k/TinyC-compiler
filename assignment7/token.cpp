#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tc_driver.hpp"

//
//                  TkInfo
//
int TC::TkInfo::get_op()         { return op_;     }
int TC::TkInfo::get_lev()        { return lev_;    }
int TC::TkInfo::get_kind()       { return kind_;   }
int TC::TkInfo::get_offset()     { return offset_; }
std::string TC::TkInfo::get_id() { return id_;     }

void TC::TkInfo::debug() {
  using namespace std;
  cout << "ID : " << id_ << endl;
  cout << "OP : " << op_ << endl;
  cout << "lev : " << lev_ << endl;
  cout << "kind : ";
  switch(kind_) {
    case (FRESH):
      cout << "FRESH";
      break;
    case (VAR):
      cout << "VAR";
      break;
    case (FUN):
      cout << "FUN";
      break;
    case (PARM):
      cout << "PARM";
      break;
    case (UNDEFFUN):
      cout << "UNDEFFUN";
      break;
  }
  cout << endl;
  cout << "offset : " << offset_ << endl;
  cout << "ADDRESS : " << this << endl;
}

//
//                  TkInfo
//


// Token_Driver
//
TC::Token_Driver::Token_Driver() : level_(0), last_alloc(0), top_alloc(0) {}

TC::Token_Driver::~Token_Driver() {}

void TC::Token_Driver::Push(TkInfo *ti) {
  idlist.push_front(ti);
  total_list.push_front(ti);
}

void TC::Token_Driver::Pop(int lev) {
  for (int i = 0; i < idlist.size(); i++) {
    if (idlist[i]->get_lev() == lev) {
      idlist.pop_front();
    } else {
      break;
    }
  }
}


void TC::Token_Driver::debug() {
  for (std::deque<TkInfo *>::iterator it = total_list.begin(); it != total_list.end(); it++) {
    std::cout << "---------------\n";
    (*it)->debug();
    std::cout << "---------------\n";
  }
}

TC::TkInfo *TC::Token_Driver::lookup_sym(std::string id) {
  for (std::deque<TkInfo *>::iterator it = idlist.begin(); it != idlist.end(); it++) {
    if ((*it)->get_id() == id) {
      return (*it);
    }
  }
  return NULL;
}

void TC::Token_Driver::globalize_sym(TkInfo *ti) {
  idlist.pop_front();
  idlist.push_back(ti);
  total_list.pop_front();
  total_list.push_back(ti);
}

// void TC::Token_Driver::set_all_offset() {
//   int current = 0;
//   for (int i = 0; i < total_list.size(); i++) {
//     // 変数宣言でなおかつ大域変数でない場合
//     if (total_list[i]->get_kind() == TC::TkInfo::VAR && total_list[i]->get_lev() >= 2) {
//       // ネストに入るか同じネスト内の場合
//       if (current <= total_list[i]->get_lev()) {
//         total_list[i]->set_offset(allocate_loc());
//         current = total_list[i]->get_lev();
//       } else {

//       }
//     }
//   }
// }

int TC::Token_Driver::allocate_loc() {
  last_alloc -= 4;
  if (last_alloc < top_alloc) {
    top_alloc = last_alloc;
  }
  return last_alloc;
}

void TC::Token_Driver::release_loc(int cnt) {
  if (cnt != 0) {
    last_alloc += (4 * cnt);
  } 
}

