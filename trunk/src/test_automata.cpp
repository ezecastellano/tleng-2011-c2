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
}

void testConcat() {
    Automata a('a');
    Automata b('b');
    a + b;
    a + a + a + a;
}

void testOr() {
    Automata a('a');
    Automata b('b');
    cout << "??" << endl;
    Automata dot('.');
    a.mostrar(cout);
    b | dot;
}

void testOp() {
    Automata a('a');
    Automata b('?');
    Automata dot('.');
    a.apply_op(b);
}

int main() {
    simpleTest();
    cout << "done1" << endl;
    testCreate();
    cout << "done2" << endl;
    testConcat();
    cout << "done3" << endl;
    testOr();
    cout << "done4" << endl;
    testOp();
    cout << "done5" << endl;
    return 0;
}
