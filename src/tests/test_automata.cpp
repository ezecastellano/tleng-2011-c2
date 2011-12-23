#include "../automata.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

string basedir("graph/dots/");
string prefix_dot("automata-");
string suffix_dot(".dot");
char id = 'a';

string next_file() {
    //~ string res = basedir + prefix_dot + id + suffix_dot;
    string res = prefix_dot + id + suffix_dot;
    cout << res << endl;
    id++;
    return res;
}


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
    fstream f;
    f.open(next_file());
    s.mostrar(f);
    f.close();
    f.open(next_file());
    e.mostrar(f);
    f.close();
    f.open(next_file());
    dot.mostrar(f);
    f.close();
    f.open(next_file());
    b.mostrar(f);
    f.close();
    f.open(next_file());
    a.mostrar(f);
    f.close();
    
}

void testOr() {
    Automata a('a');
    Automata b('b');
    Automata dot('.');
    a |= a;
    fstream f(next_file());
    a.mostrar(f);
    f.close();
    f.open(next_file());
    b |= dot;
    b.mostrar(f);
    f.close();
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
