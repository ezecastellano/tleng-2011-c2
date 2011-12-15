GCCFLAGS=-g 
#-Wall -Wextra
GCC=gcc
SOURCES = automata.c grep-line.tab.c main.c

all: grep-line

grep-line.tab.c: grep-line.y
	bison -d grep-line.y

grep-line: $(SOURCES)
	$(GCC) $(GCCFLAGS) $(SOURCES) -o grep-line

test: grep-line
	cat lineas | ./grep-line

clean:
	rm -f grep-line.tab.c grep-line
