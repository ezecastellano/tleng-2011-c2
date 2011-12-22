CXXFLAGS = -g -Wall -Wextra -std=c++0x
SOURCES = automata.cpp grep-line.tab.cpp main.cpp matcher.cpp graph.cpp
BISON = grep-line.ypp

all: grep-line

bison: $(BISON)
	bison -d -ggraph.dot $(BISON)
	dot graph.dot -Tpng -o graph.png

grep-line: bison $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o grep-line

test-graph: test_graph.cpp graph.cpp
	$(CXX) $(CXXFLAGS) test_graph.cpp  graph.cpp -o test-graph

test-automata: test_automata.cpp automata.cpp graph.cpp
	$(CXX) $(CXXFLAGS) test_automata.cpp automata.cpp graph.cpp -o test-automata

test: grep-line test-automata test-graph
	./run-test-regexp
	./test-automata
	./test-graph

clean:
	rm -f grep-line.tab.cpp grep-line.tab.hpp grep-line graph.dot graph.png test-automata
