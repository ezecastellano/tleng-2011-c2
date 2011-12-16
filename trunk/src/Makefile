CXXFLAGS = -g 
#-Wall -Wextra
SOURCES = automata.cpp grep-line.tab.cpp main.cpp
BISON = grep-line.ypp

all: grep-line

bison: $(BISON)
	bison -d -ggraph.dot $(BISON)
	dot graph.dot -Tpng -o graph.png

grep-line: bison $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o grep-line

test: grep-line
	./run-test-regexp

clean:
	rm -f grep-line.tab.cpp grep-line.tab.hpp grep-line graph.dot graph.png
