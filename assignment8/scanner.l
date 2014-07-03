%{
	#include <string>
	#include <iostream>
	#include "tc_scanner.h"
  #include "ast.h"

	typedef TC::TC_Parser::token token;
%}
%option debug
%option noyywrap
%option yyclass="TC::Scanner"
%option nodefault
%option yylineno
%option c++

delimiter 		[ \t\n]
whitespace		{delimiter}+
digit			[0-9]
number			{digit}+
letter 			[a-zA-Z]
id 				{letter}({letter}|{digit}|_)*
symbol			";"|","|"("|")"|"{"|"}"|">"|"<"|"*"|"="|"+"|"/"|"-"

%%
{whitespace}	{}

"int"			{ return token::T_Int; }

"if"			{ return token::T_If; }

"else"		{ return token::T_Else; }

"while"		{ return token::T_While; }

"return"	{ return token::T_Return; }

">="			{ return token::T_GreaterEqual; }

"<="			{ return token::T_LessEqual; }

"=="			{
            yylval->op = OP::EQUAL;
            return token::T_Equal;
          }

"!="			{ return token::T_NotEqual; }


"&&"			{
            yylval->op = OP::AND;
            return token::T_And;
          }

"||"			{
            yylval->op = OP::OR;
            return token::T_Or;
          }

{number}	{
            yylval->val = strtol(yytext, NULL, 10);
            return token::Integer;
          }

{id}			{ 
            yylval->id = new std::string(yytext);
            return token::Id;
          }

{symbol}	{ return *YYText(); }

.				  { driver.error("invalid character"); }

%%