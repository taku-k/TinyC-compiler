#ifndef __TCDRIVER_H__
#define __TCDRIVER_H__

#include <string>
#include <deque>

#include "tc_parser.tab.hh"
#include "tc_scanner.h"
#include "ast.h"
#include "token.h"
#include "codegen.h"

class CodeGen;

class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};

namespace TC{

// class Token_Driver;
// class TkInfo;

class TC_Driver {
public:

	TC_Driver() : parser(NULL),scanner(NULL),nodel(NULL),
            t_driver(NULL), semnerrs(0), null_buffer(NULL), null_stream(NULL) {};
	~TC_Driver();

  // パース関数
	void parse(const char *filename);


  // 構文木を出力する関数
  // flagがtrueなら構文木を出力する
  void print(bool flag);
  // コードを生成する
  void code_gen(bool flag);

  TC::Token_Driver *getTokenDriver() { 
    return t_driver;
  }

  // 関数呼び出し時の引数チェックを行う
  // すべての構文木を探索してから実行される 
  void func_args_check();

  // エラーを出力する関数
  void error(const std::string &err_m);
  // errorを出力する
  // エラー回数をカウントする
  void error(const char *fmt, ...);
  // warnを出力する
  void warn(const char *fmt, ...);


  // エラー回数を返す
  int get_semnerrs() { return semnerrs; }
  // エラーをカウントする
  void semnerrs_up() { semnerrs++; }

private:
  TC::TC_Parser *parser;
  TC::TC_Scanner *scanner;
  NodeList *nodel;
  TC::Token_Driver *t_driver;
  CodeGen *cg;

  std::ofstream *out;
  int semnerrs;

  NullBuffer *null_buffer;
  std::ostream *null_stream;
};





}

#endif