#ifndef __TCDRIVER_HPP__
#define __TCDRIVER_HPP__

#include <string>
#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"

namespace TC{

class TC_Driver {
public:
	TC_Driver() : parser(NULL),scanner(NULL){};
	virtual ~TC_Driver();

	void parse(const char *filename);

  void error(const std::string &err_m);
private:
	TC::TC_Parser *parser;
	TC::TC_Scanner *scanner;
};

}

#endif