%{
	#include <string>
	#include <iostream>
	#include "tc_scanner.hpp"
  #include "node.hpp"

	typedef TC::TC_Parser::token token;
%}
%option debug
%option noyywrap
%option yyclass="TC::Scanner"
%option nodefault
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
"=="			{ return token::T_Equal; }
"!="			{ return token::T_NotEqual; }
"&&"			{
            yylval->op = OP::T_AND;
            return token::T_And;
          }
"||"			{
            yylval->op = OP::T_OR;
            return token::T_Or;
          }

{number}	{ return token::Integer; }
{id}			{ 
            yylval->id = new std::string(yytext);
            return token::Identifier;
          }
{symbol}	{ return *YYText(); }
.				  {}
%%