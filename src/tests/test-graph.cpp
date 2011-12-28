#include "../graph.hpp"
#include "../debugging.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;


void testCreate() {
    LDGraph a('a');
    LDGraph b('b');
    LDGraph dot('.');
    LDGraph t(dot);
    LDGraph s = t;
    
}

void testOr() {
    LDGraph a('a');
    LDGraph b('b');
    LDGraph dot('.');
    a |= a;
    b |= dot;
    b.determinize();
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
    guardar(b);
    a |= b;
    a += a;
    a.add_jump();
}

void testthree() {
    LDGraph a('a');
    LDGraph b('b');
    a += b; // ab
    a.determinize();
    guardar(a);
    a.add_inverse_jump(); // (ab)+
    a.determinize();
    guardar(a);
}

int main() {
    cout << "Testing Graph" << endl;
    testCreate();
    testOr();
    testConcat();
    completeTest();
    testthree();
    return 0;
}
