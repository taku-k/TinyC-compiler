#include <string>
#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"

namespace TC{

class TC_Driver {
public:
	TC_Driver() : parser(NULL),scanner(NULL){};
	virtual ~TC_Driver();

	void parse();
private:
	TC::TC_Parser *parser;
	TC::TC_Scanner *scanner;
};

}

