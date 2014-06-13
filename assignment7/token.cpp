#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tc_driver.hpp"

//
//                  TkInfo
//
int TC::TkInfo::get_op() {return op_;}
int TC::TkInfo::get_lev() {return lev_;}
int TC::TkInfo::get_kind() {return kind_;}
int TC::TkInfo::get_offset() {return offset_;}

void TC::TkInfo::debug() {
  std::cout << "OP " << op_ << std::endl;
  std::cout << "lev " << lev_ << std::endl;
  std::cout << "kind " << kind_ << std::endl;
  std::cout << "offset " << offset_ << std::endl;
  std::cout << "ID " << id_ << std::endl;
}

//
//                  TkInfo
//


// Token_Driver
//
TC::Token_Driver::Token_Driver() {}

TC::Token_Driver::~Token_Driver() {}

void TC::Token_Driver::Push(TkInfo *ti) {
  t_vec.push_back(ti);
}

TC::TkInfo* TC::Token_Driver::Pop() {
  TC::TkInfo *ret = t_vec[t_vec.size()-1];
  t_vec.pop_back();
  return ret;
}

void TC::Token_Driver::add_id(std::string id) {
  idtable.push_back(id);
}

void TC::Token_Driver::debug() {
  for (int i = 0; i < t_vec.size(); i++) {
    std::cout << "-------" << i << "--------\n";
    std::cout << i << std::endl;
    t_vec[i]->debug();
    std::cout << "-------------------\n";
  }
}