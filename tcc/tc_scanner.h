#ifndef __TCSCANNER_HPP__
#define __TCSCANNER_HPP__ 1
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int  TC::TC_Scanner::yylex()

#include "tc_parser.tab.hh"
#include "tc_driver.h"

namespace TC{

class TC_Scanner : public yyFlexLexer{
public:
  int yylineno;
  TC_Scanner(std::istream *in, TC::TC_Driver &d) : 
              yyFlexLexer(in), yylval(NULL), driver(d) {};

  int yylex(TC::TC_Parser::semantic_type *lval) {
    yylval = lval;
    return(yylex());
  }
private:
  int yylex();
  TC::TC_Parser::semantic_type *yylval;
  TC::TC_Driver &driver;
};

}
#endif