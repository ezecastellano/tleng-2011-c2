#include "automata.hpp"
#include <cassert>
#include <iostream>

using namespace std;

void simpleTest(){
    Automata a;
}

void testCreate() {
    Automata a('a');
    Automata b('b');
    Automata dot('.');
    Automata e;
    Automata t(dot);
    Automata s = t;
    e.~Automata();
    s.mostrar(cout);
    e.mostrar(cout);
    dot.mostrar(cout);
    b.mostrar(cout);
    a.mostrar(cout);
    
}

void testOr() {
    Automata a('a');
    Automata b('b');
    Automata dot('.');
    a |= a;
    a.mostrar(cout);
    b |= dot;
    b.mostrar(cout);
}
void testConcat() {
    Automata a('a');
    Automata b('b');
    a += b;
    a += a;
    a += a;
    a += a;
}


void testOp() {
    Automata a('a');
    a.apply_op('?');
}

int main() {
    simpleTest();
    cout << "done1" << endl;
    testCreate();
    cout << "done2" << endl;
    testOr();
    cout << "done3" << endl;
    testConcat();
    cout << "done4" << endl;
    testOp();
    cout << "done5" << endl;
    return 0;
}
