#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <vector>

#include "tc_driver.h"
#include "token.h"

using namespace std;

class Node;
class FuncNode;
class StatList;
class IFStatNode;
class WHILEStatNode;
class RETURNStatNode;
class ExpressionList;
class AssignExprNode;
class FuncCallNode;
class DeclTypeNode;

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
  CodeGen(TC::Token_Driver *td, ostream *o);

  // 最初に呼ばれる関数
  void code_generate(NodeList *nl);

  // 大域変数の宣言
  void external_decl_gen(DeclTypeNode *dtn);

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
  void expr_list_gen(ExpressionList *epl);
  void assign_expr_gen(AssignExprNode *aen);

  void expr_gen(Node *n);

  // 関数呼び出しコード生成
  void func_call_gen(FuncCallNode *fcn);

  void release_code();

private:
  // コードを発行する関数
  void emit_code(string c);

  // ラベルを発行する関数
  string make_label();

  // 出力用stream
  ostream *out;

  // コード全体を配列で保持する
  vector<string> code;

  // return文用のラベル
  string ret_label;

  // labelの数を保持
  int label;

  // このtop_allocの値がNlocalに埋め込まれる
  int top_alloc;
  int final_temp_alloc;

  // levelに対してそのlevelでのoffsetの最大値が返される
  int create_temp_alloc();
  void release_temp() {top_alloc-=4;}

  // 一時変数分の領域を確保するコードを挿入する関数
  void insert_temp_alloc_code();
};

#endif