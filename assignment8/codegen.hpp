#ifndef __CODEGEN__
#define __CODEGEN__

#include <vector>

#include "tc_driver.hpp"
#include "token.hpp"

using namespace std;

class Node;
class FuncNode;
class StatList;
class IFStatNode;
class WHILEStatNode;
class RETURNStatNode;
class ExpressionList;

/*
 * codegenでコードを生成する
 *
 * ・算術演算時の一時変数の確保の方法
 *      各レベルごとの最大値を取得しておいて
 *      もし一時変数の確保がtop_allocを超えてしまう場合
 *      Nlocalの値をあげる 
 */

class CodeGen {
public:
  // コンストラクタ 
  CodeGen(TC::Token_Driver *td);

  // 最初に呼ばれる関数
  void code_generate(NodeList *nl);

  // 関数定義のコード生成  
  void func_decl_gen(FuncNode *fn);

  //文のコード生成
  void state_list_gen(StatList *sl);
  void state_gen(Node *n);

  // if文のコード生成
  void if_state_gen(IFStatNode *isn, bool isElse);

  // while文
  void while_state_gen(WHILEStatNode *wsn);

  // return文
  void ret_state_gen(RETURNStatNode *rsn);

  // exprのコード生成
  void expr_gen(ExpressionList *epl);

  // 論理演算式のコード生成
  //void logical_gen();

  // 関数呼び出しコード生成
  //void func_call_gen();

  

  void debug();
private:
  // コードを発行する関数
  void emit_code(string c);

  // ラベルを発行する関数
  string make_label();

  TC::Token_Driver *token_driver;
  vector<string> code;
  int label;
  // このtop_allocの値がNlocalに埋め込まれる
  int top_alloc;
  // levelに対してそのlevelでのoffsetの最大値が返される
};

#endif