%option noyywrap
%option yylineno
%{
	#include "tinycc.tab.h" 
%}
delim		[ \t\n]
ws			{delim}+
letter	[A-Za-z]
digit		[0-9]
id 			{letter}({letter}|{digit}|_)*
const 	{digit}+
symbol	";"|"."|"{"|"}"|"("|")"|"="|"||"|"&&"|"=="|"!="|"<"|">"|"<="|">="|"+"|"-"|"*"|"/"
keyword	"int"|"if"|"while"|"return"|"else"
%%
{ws}		{}
"int"				{	return T_Int;		}
"if"				{ return T_If;		}
"while"			{ return T_While;	}
"return"		{ return T_Return;}
"else"			{ return T_Else;	}
{id}		{
	return Identifier;
}
{const}	{
	yylval = atoi(yytext);
	return Integer;
}
{symbol} {
	return *yytext;
}
.	{
	yyerror("Error: invalid character");
}
%%