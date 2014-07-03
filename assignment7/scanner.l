%{
	#include <string>
	#include <iostream>
	#include "tc_scanner.hpp"
  #include "ast.hpp"

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

">="			{ 
            yylval->op = OP::GREATEREQUAL;
            return token::T_GreaterEqual; 
          }

"<="			{ 
            yylval->op = OP::LESSEQUAL;
            return token::T_LessEqual; 
          }

"=="			{
            yylval->op = OP::EQUAL;
            return token::T_Equal;
          }

"!="			{
            yylval->op = OP::NOTEQUAL;
            return token::T_NotEqual; 
          }


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