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


}

%union{
  Nnode *node;
  std::string *id;
  int op;
  int val;
}

%token  T_Int
%token  T_If
%token  T_Else
%token  T_While
%token  T_Return
%token  <id>  Identifier
%token  <val> Integer
%token  <op>  T_Equal
%token  <op>  T_Or
%token  <op>  T_And
%token  <op>  T_NotEqual
%token  <op>  T_LessEqual
%token  <op>  T_GreaterEqual


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
%type <node> relational_expr
%type <node> add_expr
%type <node> mult_expr
%type <node> unary_expr
%type <node> postfix_expr
%type <node> primary_expr
%type <node> argument_expression_list
%type <node> constant

%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <id>
%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <node>


%%

program                     : external_declaration                      { nl.add($1); }
                            | program external_declaration              { nl.add($2); }
                            ;

external_declaration        : declaration                               { $$ = $1; }
                            | function_definition                       { $$ = $1; }
                            ;

declaration                 : T_Int declarator_list ';'                 { $$ = new DeclTypeNode(OP::INT, $2); }
                            ;

declarator_list             : declarator                                { $$ = new DeclList(OP::INT, $1, NULL); }
                            | declarator_list ',' declarator            { $$ = new DeclList(OP::INT, $3, $1); }
                            ;

declarator                  : Identifier                                { /*$$ = new DeclNode($1, &driver);*/ $$ = new DeclNode(new IdentifierNode($1)); }
                            ;

function_definition         : T_Int declarator '(' ')' compound_statement                         { $$ = new FuncNode(new RetNode(OP::INT), $2, NULL, $5); }
                            | T_Int declarator '(' parameter_type_list ')' compound_statement     { $$ = new FuncNode(new RetNode(OP::INT), $2, $4, $6); }
                            ;

parameter_type_list         : parameter_declaration                           { $$ = new ParamDeclList($1, NULL); }
                            | parameter_type_list ',' parameter_declaration   { $$ = new ParamDeclList($3, $1); }
                            |                                                 { $$ = new ParamDeclList(NULL, NULL); }
                            ;

parameter_declaration       : T_Int declarator                           { $$ = new ParamDeclNode(OP::INT, $2); }
                            ;

statement                   : ';'                                                   { $$ = new StatNode(NULL); }
                            | expression ';'                                        { $$ = new StatNode($1); }
                            | compound_statement                                    { $$ = $1; }
                            | T_If '(' expression ')' statement                     { $$ = new IFStatNode($3, $5); }
                            | T_If '(' expression ')' statement T_Else statement    { $$ = new IFStatNode($3, $5, $7); }
                            | T_While '(' expression ')' statement                  { $$ = new WHILEStatNode($3, $5); }
                            | T_Return expression ';'                               { $$ = new RETURNStatNode($2); }
                            ;

compound_statement          : '{' declaration_list '}'                    { $$ = new ComStatNode($2, NULL); }
                            | '{' declaration_list statement_list '}'     { $$ = new ComStatNode($2, $3); }
                            | '{' statement_list '}'                      { $$ = new ComStatNode(NULL, $2); }
                            | '{' '}'                                     { $$ = new ComStatNode(NULL, NULL); }
                            ;

declaration_list            : declaration                                 { $$ = new DeclarationList($1, NULL); }
                            | declaration_list declaration                { $$ = new DeclarationList($2, $1); }
                            ;

statement_list              : statement                                   { $$ = new StatList($1, NULL); }
                            | statement_list statement                    { $$ = new StatList($2, $1); }
                            ;

expression                  : assign_expr                                 { $$ = new ExpressionList($1, NULL); }
                            | expression ',' assign_expr                  { $$ = new ExpressionList($3, $1); }
                            ;

assign_expr                 : logical_OR_expr                             { $$ = new AssignExprNode($1); }
                            | Identifier '=' assign_expr                  { $$ = new AssignExprNode(new IdentifierNode($1), $3); }
                            ;

logical_OR_expr             : logical_AND_expr                            { $$ = $1; }
                            | logical_OR_expr T_Or logical_AND_expr       { $$ = new ExprNode($2, $1, $3); }
                            ;

logical_AND_expr            : equality_expr                               { $$ = $1; }
                            | logical_AND_expr T_And equality_expr        { $$ = new ExprNode($2, $1, $3); }
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
                            | Identifier '(' argument_expression_list ')' { $$ = new FuncCallNode(new IdentifierNode($1), $3); }
                            ;

primary_expr                : Identifier                                  { $$ = new IdentifierNode($1); }
                            | constant                                    { $$ = $1; }
                            | '(' expression ')'                          { $$ = $2; }
                            ;

argument_expression_list    : assign_expr                                 { $$ = new FuncArgsNode($1, NULL); }
                            | argument_expression_list ',' assign_expr    { $$ = new FuncArgsNode($3, $1); }
                            |                                             { $$ = new FuncArgsNode(NULL, NULL); }
                            ;

constant                    : Integer                                     { $$ = new IntegerNode($1); }
                            ;

%%
void TC::TC_Parser::error(const std::string &m) {
  std::cerr << "Error: " << m << std::endl;
}
