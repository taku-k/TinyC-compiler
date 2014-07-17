%skeleton "lalr1.cc"
%require  "3.0"
%defines
%define api.namespace  {TC}
%define parser_class_name  {TC_Parser}

%code requires{
  namespace TC {
    class TC_Driver;
    class TC_Scanner;
  }
  class NodeList;
  class Node;
  class List;
}

%parse-param  { TC_Scanner &scanner }
%parse-param  { TC_Driver &driver   }
%parse-param  { NodeList &nl        }

%code{
  #include <fstream>
  #include <cstdlib>
  #include <iostream>
  #include <string>
  #include "tc_driver.h"

#undef yylex
#define yylex scanner.yylex

}

%union{
  Node *node;
  List *list;
  std::string *id;
  int op;
  int val;
}

%token  T_Int
%token  T_If
%token  T_Else
%token  T_While
%token  T_Return
%token  T_For
%token  T_Inc
%token  T_Dec
%token  <id>  Id
%token  <val> Integer
%token  <op>  T_Equal
%token  <op>  T_Or
%token  <op>  T_And
%token  <op>  T_NotEqual
%token  <op>  T_LessEqual
%token  <op>  T_GreaterEqual
%token  <op>  T_AddAssign
%token  <op>  T_SubAssign


%type <node> external_declaration
%type <node> declaration
%type <list> declaration_list
%type <node> declarator
%type <list> declarator_list
%type <node> function_definition
%type <node> compound_statement
%type <list> parameter_type_list
%type <node> parameter_declaration
%type <list> statement_list
%type <node> statement
%type <node> expression
%type <node> assign_expr
%type <node> logical_OR_expr
%type <node> logical_AND_expr
%type <node> equality_expr
%type <node> relational_expr
%type <node> add_expr
%type <node> mult_expr
%type <node> unary_expr
%type <node> postfix_expr
%type <node> primary_expr
%type <list> argument_expression_list
%type <node> constant
%type <node> Identifier
%type <node> func_def_declarator
%type <node> func_call_identifier
%type <node> bit_or_expr
%type <node> bit_xor_expr
%type <node> bit_and_expr


%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <id>
%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <node>
%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <list>



%%
main                        : {
                                set_tc_driver(&driver);
                                set_tc_scanner(&scanner);
                                set_token_driver(driver.getTokenDriver());
                              } 
                              program
                            ;

program                     : external_declaration                      { nl.add($1); }
                            | program external_declaration              { nl.add($2); }
                            ;

external_declaration        : declaration                               { $$ = $1; }
                            | function_definition                       { $$ = $1; }
                            ;





declaration                 : T_Int declarator_list ';'                 { $$ = new DeclTypeNode(OP::INT, $2, &driver); }
                            ;

declarator_list             : declarator                                { ($$ = new DeclList())->append($1); }
                            | declarator_list ',' declarator            { ($$ = $1)->append($3); }
                            ;


declarator                  : Identifier                                { $$ = $1; }
                            ;




function_definition         : T_Int func_def_declarator subroutien_up '(' ')' compound_statement subroutien_down  {
                                                                                                                    $$ = new FuncNode(new RetNode(OP::INT), $2, new ParamDeclList(), $6); 
                                                                                                                  }
                            | T_Int func_def_declarator subroutien_up '(' parameter_type_list ')' compound_statement subroutien_down {
                                                                                                                                        $$ = new FuncNode(new RetNode(OP::INT), $2, $5, $7); 
                                                                                                                                     }
                            ;

func_def_declarator         : declarator                                            { $$ = make_func_def($1); }
                            ;

parameter_type_list         : parameter_declaration                                 { ($$ = new ParamDeclList())->append($1); }
                            | parameter_type_list ',' parameter_declaration         { ($$ = $1)->append($3); }
                            ;

parameter_declaration       : T_Int declarator                                      { $$ = new ParamDeclNode(OP::INT, $2); }
                            ;

statement                   : ';'                                                   { $$ = new StatNode(NULL); }
                            | expression ';'                                        { $$ = new StatNode($1); }
                            | compound_statement                                    { $$ = $1; }
                            | T_If '(' expression ')' statement                     { $$ = new IFStatNode($3, $5); }
                            | T_If '(' expression ')' statement T_Else statement    { $$ = new IFStatNode($3, $5, $7); }
                            | T_While '(' expression ')' statement                  { $$ = new WHILEStatNode($3, $5); }
                            | T_Return expression ';'                               { $$ = new RETURNStatNode($2); }
                            | T_For '(' expression ';' expression ';' expression ')' statement { $$ = new FORStatNode($3, $5, $7, $9); }
                            ;

compound_statement          : subroutien_up '{' declaration_list '}' subroutien_down                 { $$ = new ComStatNode($3, new StatList()); }
                            | subroutien_up '{' declaration_list statement_list '}' subroutien_down  { $$ = new ComStatNode($3, $4); }
                            | subroutien_up '{' statement_list '}' subroutien_down                   { $$ = new ComStatNode(new DeclarationList(), $3); }
                            | subroutien_up '{' '}' subroutien_down                                  { $$ = new ComStatNode(new DeclarationList(), new StatList()); }
                            ;

subroutien_up               :                                             { (driver.getTokenDriver())->level_up(); }
                            ;

subroutien_down             :                                             {
                                                                            (driver.getTokenDriver())->Pop(driver.getTokenDriver()->get_cur_level());
                                                                            (driver.getTokenDriver())->level_down();
                                                                          }
                            ;

declaration_list            : declaration                                 { ($$ = new DeclarationList())->append($1); }
                            | declaration_list declaration                { ($$ = $1)->append($2); }
                            ;

statement_list              : statement                                   { ($$ = new StatList())->append($1); }
                            | statement_list statement                    { ($$ = $1)->append($2); }
                            ;

expression                  : assign_expr                                 { $$ = new ExpressionList($1, NULL); }
                            | expression ',' assign_expr                  { $$ = new ExpressionList($3, $1); }
                            ;

assign_expr                 : logical_OR_expr                             { $$ = new AssignExprNode($1); }
                            | Identifier '=' assign_expr                  { $$ = new AssignExprNode(OP::ASSIGN, ref_var($1), $3); }
                            | Identifier T_AddAssign assign_expr          { $$ = new AssignExprNode(OP::ADDASSIGN, ref_var($1), $3); }
                            | Identifier T_SubAssign assign_expr          { $$ = new AssignExprNode(OP::SUBASSIGN, ref_var($1), $3); }
                            ;

logical_OR_expr             : logical_AND_expr                            { $$ = $1; }
                            | logical_OR_expr T_Or logical_AND_expr       { $$ = new ExprNode($2, $1, $3); }
                            ;

logical_AND_expr            : bit_or_expr                                 { $$ = $1; }
                            | logical_AND_expr T_And bit_or_expr          { $$ = new ExprNode($2, $1, $3); }
                            ;

bit_or_expr                 : bit_xor_expr                                { $$ = $1; }
                            | bit_or_expr '|' bit_xor_expr                { $$ = new ExprNode(OP::BITOR, $1, $3); }
                            ;

bit_xor_expr                : bit_and_expr                                { $$ = $1; }
                            | bit_xor_expr '^' bit_and_expr               { $$ = new ExprNode(OP::BITXOR, $1, $3); }
                            ;

bit_and_expr                : equality_expr                               { $$ = $1; }
                            | bit_and_expr '&' equality_expr              { $$ = new ExprNode(OP::BITAND, $1, $3); }
                            ;

equality_expr               : relational_expr                             { $$ = $1; }
                            | equality_expr T_Equal relational_expr       { $$ = new ExprNode($2, $1, $3); }
                            | equality_expr T_NotEqual relational_expr    { $$ = new ExprNode($2, $1, $3); }
                            ;

relational_expr             : add_expr                                    { $$ = $1; }
                            | relational_expr '<' add_expr                { $$ = new ExprNode(OP::LESS, $1, $3); }
                            | relational_expr '>' add_expr                { $$ = new ExprNode(OP::GREATER, $1, $3); }
                            | relational_expr T_GreaterEqual add_expr     { $$ = new ExprNode(OP::GREATEREQUAL, $1, $3); }
                            | relational_expr T_LessEqual add_expr        { $$ = new ExprNode(OP::LESSEQUAL, $1, $3); }
                            ;

add_expr                    : mult_expr                                   { $$ = $1; }
                            | add_expr '+' mult_expr                      { $$ = new ExprNode(OP::ADD, $1, $3); }
                            | add_expr '-' mult_expr                      { $$ = new ExprNode(OP::SUB, $1, $3); }
                            ;

mult_expr                   : unary_expr                                  { $$ = $1; }
                            | mult_expr '*' unary_expr                    { $$ = new ExprNode(OP::MUL, $1, $3); }
                            | mult_expr '/' unary_expr                    { $$ = new ExprNode(OP::DIV, $1, $3); }
                            ;

unary_expr                  : postfix_expr                                { $$ = $1; }
                            | '-' unary_expr                              { $$ = new UnaryNode(OP::MINUS, $2); }
                            ;

postfix_expr                : primary_expr                                { $$ = $1; }
                            | func_call_identifier '(' argument_expression_list ')' { $$ = new FuncCallNode($1, $3); }
                            | func_call_identifier '(' ')'                          { $$ = new FuncCallNode($1, new FuncArgsList());}
                            ;

func_call_identifier        : Identifier                                  { $$ = ref_func($1); }
                            ;

primary_expr                : Identifier                                  { $$ = ref_var($1); }
                            | constant                                    { $$ = $1; }
                            | '(' expression ')'                          { $$ = $2; }
                            ;

argument_expression_list    : assign_expr                                 { ($$ = new FuncArgsList())->append($1); }
                            | argument_expression_list ',' assign_expr    { ($$ = $1)->append($3); }
                            ;

constant                    : Integer                                     { $$ = new IntegerNode($1); }
                            ;

Identifier                  : Id                                          { $$ = make_identifier(*$1); }
                            ;


%%
void TC::TC_Parser::error(const std::string &m) {
  std::cerr << "Parser Error: " << m << std::endl;
}
