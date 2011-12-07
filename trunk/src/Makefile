
all: grep-line

grep-line.tab.c: grep-line.y
	bison grep-line.y

grep-line: grep-line.tab.c
	gcc grep-line.tab.c -o grep-line
	rm grep-line.tab.c

test: grep-line
	cat lineas | ./grep-line

clean:
	rm -f grep-line.tab.c grep-line
