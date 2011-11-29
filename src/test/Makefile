
all: parser

rpn.tab.c: rpn.y
	bison rpn.y

parser: rpn.tab.c
	gcc rpn.tab.c -o calc

test: parser
	cat cuentas | ./calc

clean:
	rm -f rpn.tab.c calc
