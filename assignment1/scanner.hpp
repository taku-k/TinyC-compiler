#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int  TC::Scanner::yylex()


namespace TC{

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in) {};
   int yylex();
   //const char* YYText();
};
}

#endif /* END __MCSCANNER_HPP__ */
