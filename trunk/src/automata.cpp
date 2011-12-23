#include "automata.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <execinfo.h>
#include <string>

using namespace std;

Automata::Automata() : graph('/') { }


//Builds an alfanum automata
Automata::Automata(char c) : graph(c) { }

//determinize the automata
void Automata::determinize(){
    graph.determinize();
}

// ---------------  operators ----------------------------------------

void Automata::operator|=(Automata & other){
    if(this == &other)
        return;
    graph |= other.graph;
    determinize();
    return;
}
//Concatenate two automata
void Automata::operator+=(Automata & other){
    graph += other.graph;
    return;
}

//Apply unary operator
Automata & Automata::apply_op(const char c){
    
    if(c == '?' || c == '*'){
        // Enable not to match this automata.
        graph.add_jump();
    } 
    
    if (c == '+' || c == '*'){
        // Enable to match  this automata many times.(self loop)
        graph.add_inverse_jump();
    }
    determinize();
    return *this;
}

//Match a string
bool Automata::match(string s){
    State actual = graph.init();
    string::iterator c = s.begin();
    while( c != s.end() and graph.can_move(actual, *c) ) {
        Dstate t;
        graph.move_state(actual, *c, t);
        //MUST BE A DETERMINISTIC FINITE AUTOMATA
        assert(t.size() == 1);
        actual = *(t.begin());
        c++;
    }
    return true;
    //~ return graph.is_accepted(actual) and c == s.end();
}



//----------------- DISPLAY ------------------------------------
void Automata::mostrar(ostream & o) const {
    o << graph << endl;
}
ostream& operator <<(ostream& o, const Automata & a) {
    a.mostrar(o);
    return o;
}
