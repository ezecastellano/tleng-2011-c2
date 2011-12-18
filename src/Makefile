CXXFLAGS = -g -Wall -Wextra
SOURCES = automata.cpp grep-line.tab.cpp main.cpp matcher.cpp
BISON = grep-line.ypp

all: grep-line

bison: $(BISON)
	bison -d -ggraph.dot $(BISON)
	dot graph.dot -Tpng -o graph.png

grep-line: bison $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o grep-line

test-automata: test_automata.cpp automata.cpp automata.hpp
	$(CXX) $(CXXFLAGS) test_automata.cpp automata.cpp -o test-automata

test: grep-line test-automata
	./run-test-regexp

clean:
	rm -f grep-line.tab.cpp grep-line.tab.hpp grep-line graph.dot graph.png test-automata
