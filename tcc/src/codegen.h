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
class FORStatNode;


// 一行のコード情報を管理するクラス
class Code {
public:
  Code(string tag0, string tag1="", string tag2="", bool flag = false);
  ~Code() {};
  string form_code();
  string get_tag(int num);
  void set_tag(int num, string t);
  bool is_label();
private:
  bool label_flag;
  string tag[3];
};


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

  // for
  void for_state_gen(FORStatNode *fsn);

  // exprのコード生成
  void expr_list_gen(ExpressionList *epl);
  void assign_expr_gen(AssignExprNode *aen);

  void expr_gen(Node *n);

  // 関数呼び出しコード生成
  void func_call_gen(FuncCallNode *fcn);

  void general_expr_gen(string expr, Node *n);

  void general_cmp_gen(string cmp, Node *n);

  void general_logical_gen(string logical, Node *n);

  // コードを出力ストリームに流す
  // この時同時にコードの最適化関数を呼び出す
  void release_code(bool flag);


private:
  // コードを発行する関数
  void emit_code(Code *c);
  // void emit_code(string tag0, string tag1, string tag2, bool flag = false);

  // ラベルを発行する関数
  string make_label();

  // 出力用stream
  ostream *out;

  // コード全体を配列で保持する
  // vector<string> code;
  vector<Code *> codes;

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

  // コード最適化関数
  void optimize_code();

};



#endif