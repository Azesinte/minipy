CXX=g++
LEX=flex
YACC=bison

DEBUG=
CXXFLAGS=-std=c++11 $(DEBUG)
LEX_SOURCE=minipy-lab.l
YACC_SOURCE=minipy-lab.y

O_FILES= lex.yy.o y.tab.o OP_miniPY.o

main: $(O_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@./main
	
lex.yy.o: lex.yy.cc mainhead.hpp OP_miniPY.hpp y.tab.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

y.tab.o: y.tab.c mainhead.hpp OP_miniPY.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
OP_miniPY.o : OP_miniPY.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lex.yy.cc: minipy-lab.l mainhead.hpp y.tab.h 
	$(LEX) -o $@ $<

y.tab.c: $(YACC_SOURCE) mainhead.hpp 
	$(YACC) -d -o $@ $<

y.tab.h: $(YACC_SOURCE) mainhead.hpp 
	$(YACC) -d -o y.tab.cc $<


	
clean:
	rm lex.yy.cc y.tab.c y.tab.h *.o *.hh main
