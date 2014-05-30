%option noyywrap
%{
  #include <string>
  #include <iostream>
  #include "scanner.hpp"
  int yylval;
%}
%option debug 
%option nodefault 
%option yyclass="TC::Scanner" 
%option noyywrap 
%option c++

digit             [0-9]
%%
{digit}+          {
    std::cout << "Int = " << YYText() <<std::endl; 
}
"+"|"*" {
    std::cout << "Opr = " << YYText() << std::endl;
}
[ \t\n]   ;
.         ;
%%
int main(){
  TC::Scanner *s = new TC::Scanner(&std::cin);
  while(s->yylex() != 0)
    ;
  return 0;
}