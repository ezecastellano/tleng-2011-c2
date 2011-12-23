#include "../graph.hpp"
#include <cassert>
#include <iostream>

using namespace std;


void testCreate() {
    LDGraph a('a');
    LDGraph b('b');
    LDGraph dot('.');
    LDGraph t(dot);
    LDGraph s = t;
    //~ s.mostrar(cout);
    //~ e.mostrar(cout);
    //~ dot.mostrar(cout);
    //~ b.mostrar(cout);
    //~ a.mostrar(cout);
    
}

void testOr() {
    LDGraph a('a');
    LDGraph b('b');
    LDGraph dot('.');
    a |= a;
    //~ a.mostrar(cout);
    b |= dot;
    //~ b.determinize();
    //~ b.mostrar(cout);
}
void testConcat() {
    LDGraph a('a');
    LDGraph b('b');
    a += b;
    a += a;
    a += a;
    a += a;
}



void completeTest() {
    LDGraph a('a');
    LDGraph b('b');
    LDGraph dot('.');
    a |= b;
    b += b;
    b.add_inverse_jump();
    b.add_jump();
    b.determinize();
    b.mostrar(cout);
    a |= b;
    a += a;
    a.add_jump();
    //~ a.determinize();
    //~ a.mostrar(cout);
    //~ a.mostrar(cout);
}

int main() {
    testCreate();
    testOr();
    testConcat();
    completeTest();
    return 0;
}
