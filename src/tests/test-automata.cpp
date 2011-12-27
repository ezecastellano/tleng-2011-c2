#include "../automata.hpp"
#include "../debugging.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

void testCreate() {
    Automata a('a');
    Automata b('b');
    Automata dot('.');
    Automata e;
    Automata t(dot);
    Automata s = t;
    t = e;
    guardar(s);
    guardar(t);
    guardar(e);
    guardar(dot);
    guardar(b);
    guardar(a);
    
}

void testOr() {
    Automata a('a');
    Automata b('b');
    Automata dot('.');
    a |= a;
    guardar(a);
    b |= dot;
    guardar(b);
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

void finalTest() {
    Automata a('a');
    Automata b('b');
    Automata c('c');
    Automata d('d');
    c += a; // ca
    c.apply_op('+'); // (ca)+
    b+=c; // b(ca)+
    b+=d;
    b.determinize();
    guardar(b);
}

void testO() {
    Automata a('a');
    Automata b('b');
    a |= b;
    a.determinize();
    guardar(a, "testO");
}

int main() {
    cout << "Testing Automata" << endl;
    testCreate();
    testOr();
    testConcat();
    testOp();
    finalTest();
    testO();
    return 0;
}
