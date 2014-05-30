#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int  TC::TC_Scanner::yylex()

#include "tc_parser.tab.hh"


namespace TC{

class TC_Scanner : public yyFlexLexer{
public:
	TC_Scanner(std::istream *in) : yyFlexLexer(in) {};

	int yylex(TC::TC_Parser::semantic_type *lval) {
		return(yylex());
	}
private:
	int yylex();
};

}