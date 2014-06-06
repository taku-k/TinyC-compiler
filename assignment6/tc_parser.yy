%skeleton "lalr1.cc"
%require	"3.0"
%defines
%define api.namespace	{TC}
%define parser_class_name	{TC_Parser}

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
	char *idd;
}

%token	T_Int
%token	T_If
%token	T_Else
%token	T_While
%token	T_Return
%token	<id>	Identifier
%token	Integer
%token	T_Equal
%token	T_Or
%token	T_And
%token	T_NotEqual
%token	T_LessEqual
%token	T_GreaterEqual


%type <node> external_declaration
%type <node> declaration
%type <node> declaration_list
%type <node> declarator
%type <node> declarator_list

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <id>


%%

program:
	external_declaration	{ nl.add($1); }
	|	program external_declaration	{ nl.add($2); }
	;
external_declaration:
	declaration 	{ $$ = $1; }
	| function_definition		{}
	;
declaration:
	T_Int declarator_list ';'	{ $$ = new DeclIntListNode(OP::INT, $2); }
	;
declarator_list:
	declarator 		{ $$ = $1; }
	| declarator ',' declarator_list	{ $$ = new DeclIntListNode(OP::INT, $1, $3); }
	;
declarator:
	Identifier	{ $$ = new DeclIntNode($1); }
	;
function_definition:
	T_Int declarator '(' ')' compound_statement		{}
	| T_Int declarator '(' parameter_type_list ')' compound_statement		{}
	;
parameter_type_list:
	parameter_declaration		{}
	| parameter_type_list ',' parameter_declaration		{}
	;
parameter_declaration:
	T_Int declarator 		{}
	;
statement:
	';'
	| expression ';'	{}
	| compound_statement	{}
	| T_If '(' expression ')' statement 	{}
	| T_If '(' expression ')' statement T_Else statement 		{}
	| T_While '(' expression ')' statement 		{}
	| T_Return expression ';'		{}
	;
compound_statement:
	'{' declaration_list '}'						{}
	| '{' declaration_list statement_list '}'		{}
	| '{' statement_list '}'	{}
	| '{' '}'	{}
	;
declaration_list:
	declaration 	{}
	| declaration_list declaration		{}
	;
statement_list:
	statement 	{}
	| statement_list statement 		{}
	;
expression:
	assign_expr 	{}
	| expression ',' assign_expr 		{}
	;
assign_expr:
	logical_OR_expr 	{}
	| Identifier '=' assign_expr 	{}
	;
logical_OR_expr:
	logical_AND_expr 		{}
	| logical_OR_expr T_Or logical_AND_expr 	{}
	;
logical_AND_expr:
	equality_expr 	{}
	| logical_AND_expr T_And equality_expr 	{}
	;
equality_expr:
	relational_expr 	{}
	| equality_expr T_Equal relational_expr 		{}
	| equality_expr T_NotEqual relational_expr 		{}
	;
relational_expr:
	add_expr 		{}
	| relational_expr '<' add_expr 		{}
	| relational_expr '>' add_expr 		{}
	| relational_expr T_GreaterEqual add_expr 	{}
	| relational_expr T_LessEqual add_expr 	{}
	;
add_expr:
	mult_expr		{}
	| add_expr '+' mult_expr 		{}
	| add_expr '-' mult_expr 		{}
	;
mult_expr:
	unary_expr 		{}
	| mult_expr '*' unary_expr 		{}
	| mult_expr '/' unary_expr 		{}
	;
unary_expr:
	postfix_expr 		{}
	| '-' unary_expr		{}
	;
postfix_expr:
	primary_expr 		{}
	| Identifier '(' argument_expression_list ')'
	;
primary_expr:
	Identifier 		{}
	| constant 	{}
	| '(' expression ')'
	;
argument_expression_list:
	assign_expr 		{}
	| argument_expression_list ',' assign_expr 		{}
	|		{}
	;
constant:
	Integer 	{}
	;
%%
void TC::TC_Parser::error(const std::string &m) {
	std::cerr << "Error: " << m << std::endl;
}
