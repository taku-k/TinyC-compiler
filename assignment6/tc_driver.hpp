#ifndef __TCDRIVER_HPP__
#define __TCDRIVER_HPP__ 1

#include <string>

#include "tc_parser.tab.hh"
#include "tc_scanner.hpp"
#include "node.hpp"

namespace TC{

class TC_Driver {
public:
  static NodeList nl;

	TC_Driver() : parser(NULL),scanner(NULL),nodel(NULL){};
	virtual ~TC_Driver();

	void parse();

  void print();

  void debug();

  void AddId(std::string id);
  // NodeList* getNodeList(void) {
  //   if (nodel == NULL) {
  //     nodel = new NodeList();
  //   }
  //   return nodel;
  // }

private:
  TC::TC_Parser *parser;
  TC::TC_Scanner *scanner;
  NodeList *nodel;

  std::vector<std::string> idtable;
};

}

#endif