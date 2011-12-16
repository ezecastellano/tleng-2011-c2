#include "automata.hpp"
#include <iostream>
#include <cassert>

using namespace std;

Automata::Automata() {
    init = new Transition(LAMBDA);
    tail = init;
}

Automata::Automata(const Automata & other ) {
    cout << "AAAAAAAAAAA" << endl;
}

//Builds an alfanum automata
Automata::Automata(char c){
    cout << init << endl;
    init = new Transition(c);
    tail = init;
}
//determinize the automata
void Automata::determinize(){
    cout << "Determinize" << endl;
}

Automata & Automata::operator|(Automata & other){
    Transition* new_init = new Transition(LAMBDA);
    Transition* new_tail = new Transition(LAMBDA);
    new_init->add_next(other.init);
    new_init->add_next(init);
    other.tail->add_next(new_tail);
    tail->add_next(new_tail);
    init = new_init;
    tail = new_tail;
    return *this;
}
//Concatenate two automata
Automata & Automata::operator+(Automata & other){
    assert(tail != NULL);
    tail->add_next(other.init);
    tail = other.tail;
    return *this;
}
//Apply unary operator
Automata & Automata::apply_op(Automata & oper){
    Transition* new_init = new Transition(LAMBDA);
    Transition* new_tail = new Transition(LAMBDA);
    
    // Idem potente
    new_init->add_next(init);
    tail->add_next(new_tail);
    
    if(oper.init->c == '?' || oper.init->c == '*'){
        // Enable not to match this automata.
        new_init->add_next(new_tail);
    } 
    
    if (oper.init->c == '+' || oper.init->c == '*'){
        // Enable to match  this automata many times.
        tail->add_next(init);
    }
    
    init = new_init;
    tail = new_tail;
    return *this;
}

Automata & Automata::new_any() {
    cout << "Build any automata" << endl;
    Automata * res = new Automata();
    res -> init = new Transition(DOT);
    res -> tail = res->init;
    return *res;
}

//Match a string
bool Automata::match(string){
    cout << "Match a string" << endl;
}

Automata::Transition::Transition(int code){
    assert(code != CHAR);
    this->code = code;
}


Automata::Transition::Transition(char c){
    this->c = c;
    code = CHAR;
    
}
void Automata::Transition::add_next(Transition* t){
    next.push_back(t);
}
