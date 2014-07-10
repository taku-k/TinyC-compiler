#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tc_driver.h"

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
    nodel = new NodeList(this);
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

void TC::TC_Driver::print(bool flag) {
  // 構文木を出力しない設定 
  if (flag == false) {
    std::cout.setstate(std::ios_base::badbit);
  }
  nodel->PrintTree(std::cout);
}


void TC::TC_Driver::error(const char *fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  semnerrs_up();
  fprintf(stderr, "%d: ", scanner->yylineno);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "\n");
  va_end(argp);
}

void TC::TC_Driver::warn(const char *fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  fprintf(stderr, "%d: warning: ", scanner->yylineno);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "\n");
  va_end(argp);
}


// 関数呼び出しの引数チェック関数
// token.hppから関数呼び出しのリストとidlistよを取得してくる
// その２つのoffsetを照らしあわせてチェックする
// ただし未定義関数の場合は飛ばす
void TC::TC_Driver::func_args_check() {
  std::vector<std::pair<std::string, int> > cl = t_driver->get_func_call_list();
  std::deque<TkInfo *> fl = t_driver->get_id_list();

  for (int cl_i = 0; cl_i < cl.size(); cl_i++) {
    std::string id = cl[cl_i].first;
    int args_size = cl[cl_i].second;
    // std::cout << id << " " << args_size << std::endl;


    for (int fl_i = 0; fl_i < fl.size(); fl_i++) {
      TkInfo *ti = fl[fl_i];

      if (ti->get_offset() == TC::TkInfo::UNDEFFUN) {
        continue;
      }
      // 同名の関数でかつグローバル領域にあるものを見つけた場合
      if (ti->get_id() == id && ti->get_lev() == 0) {
        // 引数の数をチェックする
        // 引数が少ない場合
        if (ti->get_offset() > args_size) {
          // エラー処理を行う
          error("too few arguments to function `%s`", id.c_str());
        } else if (ti->get_offset() < args_size) {
          // 多い場合もエラー 
          error("too many arguments to function `%s`", id.c_str());
        }
      }
    }
  }
}


void TC::TC_Driver::code_gen(const char *filename, bool flag) {
  if (!flag) {
    out = new ofstream(filename);
    cg = new CodeGen(t_driver, out);
  } else {
    cg = new CodeGen(t_driver, &cout);
  }

  cg->code_generate(nodel);
  cg->release_code();
}