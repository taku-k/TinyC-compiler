CXX = gcc

EXE = tcc

CXXDEBUG = -g

CXXSTD = -lstdc++

CXXFLAGS = $(CXXDEBUG)


CXXOBJ = tcc tc_driver token ast codegen
SOBJ =  parser scanner

FILES = $(addsuffix .cc, $(CXXOBJ))

OBJS  = $(addsuffix .o, $(CXXOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 tc_parser.tab.cc tc_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh tc_parser.output parser.o \
				 scanner.o tc_scanner.yy.cc $(EXE)\

.PHONY: all
all: tcc

tcc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o scanner.o $(CXXSTD)


parser: tc_parser.yy
	/home/012/a0124973/3sw/bin/bison -d -v tc_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o tc_parser.tab.cc $(CXXSTD)

scanner: scanner.l
	flex --outfile=tc_scanner.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c tc_scanner.yy.cc -o scanner.o $(CXXSTD)


.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

