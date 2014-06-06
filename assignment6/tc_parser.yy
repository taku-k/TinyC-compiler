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
  class Nnode;
}

%parse-param  { TC_Scanner &scanner }
%parse-param  { TC_Driver &driver   }
%parse-param  { NodeList &nl        }

%code{
  #include <fstream>
  #include <cstdlib>
  #include <iostream>
  #include <string>
  #include "tc_driver.hpp"

#undef yylex
#define yylex scanner.yylex

  int TYPE;

}

%union{
  Nnode *node;
  std::string *id;
	int op;
}

%token  T_Int
%token  T_If
%token  T_Else
%token  T_While
%token  T_Return
%token  <id>  Identifier
%token  Integer
%token  T_Equal
%token  <op> T_Or
%token  <op> T_And
%token  T_NotEqual
%token  T_LessEqual
%token  T_GreaterEqual


%type <node> external_declaration
%type <node> declaration
%type <node> declaration_list
%type <node> declarator
%type <node> declarator_list
%type <node> function_definition
%type <node> compound_statement
%type <node> parameter_type_list
%type <node> parameter_declaration
%type <node> statement_list
%type <node> statement
%type <node> expression
%type <node> assign_expr
%type <node> logical_OR_expr
%type <node> logical_AND_expr
%type <node> equality_expr

%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <id>
%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <node>


%%

program:
  external_declaration  { nl.add($1); }
  |  program external_declaration  { nl.add($2); }
  ;
external_declaration:
  declaration   { $$ = $1; }
  | function_definition    { $$ = $1; }
  ;
declaration:
  T_Int declarator_list ';'  { $$ = new DeclTypeNode(OP::INT, $2); }
  ;
declarator_list:
  declarator     { $$ = new DeclList(OP::INT, $1, NULL); }
  | declarator_list ',' declarator   { $$ = new DeclList(OP::INT, $3, $1); }
  ;
declarator:
  Identifier  { /*$$ = new DeclNode($1, &driver);*/ $$ = new DeclNode($1); }
  ;
function_definition:
  T_Int declarator '(' ')' compound_statement    { $$ = new FuncNode(new RetNode(OP::INT), $2, NULL, $5); }
  | T_Int declarator '(' parameter_type_list ')' compound_statement    { $$ = new FuncNode(new RetNode(OP::INT), $2, $4, $6); }
  ;
parameter_type_list:
  parameter_declaration    { $$ = new ParamDeclList($1, NULL); }
  | parameter_type_list ',' parameter_declaration    { $$ = new ParamDeclList($3, $1); }
  ;
parameter_declaration:
  T_Int declarator     { $$ = new ParamDeclNode(OP::INT, $2); }
  ;
statement:
  ';'    { $$ = new StatNode(NULL); }
  | expression ';'  { $$ = $1; }
  | compound_statement  { $$ = $1; }
  | T_If '(' expression ')' statement   { $$ = new IFStatNode($3, $5); }
  | T_If '(' expression ')' statement T_Else statement     { $$ = new IFStatNode($3, $5, $7); }
  | T_While '(' expression ')' statement     { $$ = new WHILEStatNode($3, $5); }
  | T_Return expression ';'    { $$ = new RETURNStatNode($2); }
  ;
compound_statement:
  '{' declaration_list '}'  { $$ = new ComStatNode($2, NULL); }
  | '{' declaration_list statement_list '}'    { $$ = new ComStatNode($2, $3); }
  | '{' statement_list '}'  { $$ = new ComStatNode(NULL, $2); }
  | '{' '}'  { $$ = new ComStatNode(NULL, NULL); }
  ;
declaration_list:
  declaration   { $$ = new DeclarationList($1, NULL); }
  | declaration_list declaration     { $$ = new DeclarationList($2, $1); }
  ;
statement_list:
  statement   { $$ = new StatList($1, NULL); }
  | statement_list statement     { $$ = new StatList($1, $2); }
  ;
expression:
  assign_expr   { $$ = new ExpressionList($1, NULL); }
  | expression ',' assign_expr     { $$ = new ExpressionList($3, $1); }
  ;
assign_expr:
  logical_OR_expr   { $$ = new AssignExprNode($1); }
  | Identifier '=' assign_expr   { $$ = new AssignExprNode($1, $3); }
  ;
logical_OR_expr:
  logical_AND_expr     { $$ = $1; }
  | logical_OR_expr T_Or logical_AND_expr   { $$ = new ExprNode($2, $1, $3); }
  ;
logical_AND_expr:
  equality_expr   { $$ = $1; }
  | logical_AND_expr T_And equality_expr   { $$ = new ExprNode($2, $1, $3); }
  ;
equality_expr:
  relational_expr   {$$ = NULL;}
  | equality_expr T_Equal relational_expr     {}
  | equality_expr T_NotEqual relational_expr     {}
  ;
relational_expr:
  add_expr     {}
  | relational_expr '<' add_expr     {}
  | relational_expr '>' add_expr     {}
  | relational_expr T_GreaterEqual add_expr   {}
  | relational_expr T_LessEqual add_expr   {}
  ;
add_expr:
  mult_expr    {}
  | add_expr '+' mult_expr     {}
  | add_expr '-' mult_expr     {}
  ;
mult_expr:
  unary_expr     {}
  | mult_expr '*' unary_expr     {}
  | mult_expr '/' unary_expr     {}
  ;
unary_expr:
  postfix_expr     {}
  | '-' unary_expr    {}
  ;
postfix_expr:
  primary_expr     {}
  | Identifier '(' argument_expression_list ')'
  ;
primary_expr:
  Identifier     {}
  | constant   {}
  | '(' expression ')'
  ;
argument_expression_list:
  assign_expr     {}
  | argument_expression_list ',' assign_expr     {}
  |    {}
  ;
constant:
  Integer   {}
  ;
%%
void TC::TC_Parser::error(const std::string &m) {
  std::cerr << "Error: " << m << std::endl;
}
