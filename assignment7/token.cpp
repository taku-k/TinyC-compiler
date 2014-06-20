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
TC::Token_Driver::Token_Driver() {}

TC::Token_Driver::~Token_Driver() {}

void TC::Token_Driver::Push(TkInfo *ti) {
  idlist.push_front(ti);
  debuglist.push_front(ti);
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
  for (std::deque<TkInfo *>::iterator it = debuglist.begin(); it != debuglist.end(); it++) {
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
  debuglist.pop_front();
  debuglist.push_back(ti);
}

