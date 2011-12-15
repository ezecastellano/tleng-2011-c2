
all: parser

rpn.tab.cpp: rpn.ypp
	bison rpn.ypp

parser: rpn.tab.cpp
	g++ rpn.tab.cpp -o calc

test: parser
	cat cuentas | ./calc

clean:
	rm -f rpn.tab.cpp calc
