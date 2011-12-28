CXXFLAGS = -g -Wall -Wextra -std=c++0x
LDFLAGS = $(CXXFLAGS)
ABSOBJ = automata grep-line.tab main matcher graph graph_utils tests/test-automata tests/test-graph debugging
SOURCES= $(addsuffix .cpp, $(ABSOBJ))
OBJ = $(addsuffix .o, $(ABSOBJ))
BISON = grep-line.ypp
MAIN_OBJ = automata.o grep-line.tab.o main.o matcher.o graph.o graph_utils.o debugging.o
GRAPH_TEST_OBJ = graph.o graph_utils.o tests/test-graph.o debugging.o
AUTOMATA_TEST_OBJ = automata.o graph.o graph_utils.o tests/test-automata.o debugging.o


grep-line: bison-build $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) -o $@

clean:
	rm -f *.o tests/*.o
	rm -f graph/*.png graph/dot/*.dot
	rm -f grep-line.tab.*
	rm -f grep-line test-automata test-graph
	rm -f deps

bison-build: $(BISON)
	bison -d $(BISON)

bison:$(BISON)
	bison -d -ggraph/dots/grammar.dot $(BISON)
	dot graph/dots/grammar.dot -Tpng -o graph/grammar.png

grep-line.tab.cpp: bison-build
	
deps: 
	$(CXX) $(CXXFLAGS) -MM -MP  $(SOURCES) > $@

-include deps



test-graph: $(GRAPH_TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-automata: $(AUTOMATA_TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

build-test: grep-line test-automata test-graph

test: build-test
	./tests/run-test-regexp
	./test-automata
	./test-graph


