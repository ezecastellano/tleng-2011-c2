CXXFLAGS = -g 
#-Wall -Wextra
SOURCES = automata.cpp grep-line.tab.cpp main.cpp
BISON = grep-line.ypp

all: grep-line

grep-line.tab.cpp: $(BISON)
	bison -d $(BISON)

grep-line: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o grep-line

test: grep-line
	cat lineas | ./grep-line

clean:
	rm -f grep-line.tab.cpp grep-line.tab.hpp grep-line
