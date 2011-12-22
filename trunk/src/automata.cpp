#include "automata.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <execinfo.h>

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
bool Automata::match(string){
    cout << "Match a string" << endl;
    return true;
}



//----------------- DISPLAY ------------------------------------
void Automata::mostrar(ostream & o) const {
    o << graph << endl;
}
ostream& operator <<(ostream& o, const Automata & a) {
    a.mostrar(o);
    return o;
}
