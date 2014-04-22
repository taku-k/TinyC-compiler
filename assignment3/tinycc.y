%{
	#include <stdio.h>
%}
%error_verbose
%token Integer Identifier 
%token T_Int T_If T_Else T_While T_Return


%%
program:
	external_declaration	{}
	|	program external_declaration	{}
	;
external_declaration:
	declaration 	{}
	| function_definition		{}
	;
declaration:
	T_Int declarator_list ';'	{}
	;
declarator_list:
	declarator 		{}
	| declarator ',' declarator_list	{}
	;
declarator:
	Identifier	{}
	;
function_definition:
	T_Int declarator '(' parameter_type_list ')' compound_statement		{}
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
	'{' declaration_list statement_list '}'		{}
	;
declaration_list:
	declaration 	{}
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
	| logical_OR_expr "||" logical_AND_expr 	{}
	;
logical_AND_expr:
	equality_expr 	{}
	| logical_AND_expr "&&" equality_expr 	{}
	;
equality_expr:
	relational_expr 	{}
	| equality_expr "==" relational_expr 		{}
	| equality_expr "!=" relational_expr 		{}
	;
relational_expr:
	add_expr 		{}
	| relational_expr '<' add_expr 		{}
	| relational_expr '>' add_expr 		{}
	| relational_expr ">=" add_expr 	{}
	| relational_expr "<=" add_expr 	{}
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
	;
constant:
	Integer 	{}
	;
%%
extern int yylineno;
int yyerror(char *s) {
	fprintf(stderr, "%d: %s\n", yylineno, s);
	return 0;
}
main()
{
	yyparse();
}
