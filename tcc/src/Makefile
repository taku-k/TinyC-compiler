CXX = gcc

EXE = tcc

CXXDEBUG = -g

CXXSTD = -lstdc++

CXXFLAGS = $(CXXDEBUG)


CXXOBJ = tcc tc_driver ast token codegen
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
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o scanner.o $(LIBS) $(CXXSTD)

parser: tc_parser.yy
	bison -d -v tc_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o tc_parser.tab.cc

scanner: scanner.l
	flex --outfile=tc_scanner.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c tc_scanner.yy.cc -o scanner.o

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
