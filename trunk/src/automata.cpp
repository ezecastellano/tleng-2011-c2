#include "automata.hpp"
#include <iostream>
#include <cassert>
#include <map>

using namespace std;

Automata::Automata() {
    init = NULL;
    tail = init;
}

Automata::~Automata() {
    init = NULL;
    tail = NULL;
    delete_all();
}


Automata & Automata::operator = (const Automata & other) {
    if(this == &other)
        return *this;
    delete_all();
    init = other.init;
    tail = other.tail;
    synchronize(other);
    return *this;
}

//Builds an alfanum automata
Automata::Automata(char c){
    if(c == '.') {
        init = new Transition(DOT);
    } else {
        init = new Transition(c);
    }
    tail = init;
    transitions.insert(init);
}

//determinize the automata
void Automata::determinize(){
    cout << "Determinize" << endl;
}

// ---------------  operators ----------------------------------------

Automata & Automata::operator|(Automata & other){
    Transition* new_init = new Transition(LAMBDA);
    Transition* new_tail = new Transition(LAMBDA);
    //Fork
    new_init->add_next(other.init);
    new_init->add_next(init);
    //Join
    other.tail->add_next(new_tail);
    tail->add_next(new_tail);
    //rename
    init = new_init;
    tail = new_tail;
    
    //memory managment
    transitions.insert(new_init);
    transitions.insert(new_tail);
    synchronize(other);
    return *this;
}
//Concatenate two automata
Automata & Automata::operator+(Automata & other){
    //Bind
    tail->add_next(other.init);
    tail = other.tail;
    
    //MM
    synchronize(other);
    return *this;
}

//Apply unary operator
Automata & Automata::apply_op(Automata & oper){
    Transition* new_init = new Transition(LAMBDA);
    Transition* new_tail = new Transition(LAMBDA);
    
    // Extend with lambda
    new_init->add_next(init);
    tail->add_next(new_tail);
    
    if(oper.init->label == '?' || oper.init->label == '*'){
        // Enable not to match this automata.
        new_init->add_next(new_tail);
    } 
    
    if (oper.init->label == '+' || oper.init->label == '*'){
        // Enable to match  this automata many times.
        tail->add_next(init);
    }
    
    init = new_init;
    tail = new_tail;
    
    transitions.insert(init);
    transitions.insert(tail);
    
    return *this;
}

//~ //Match a string
//~ bool Automata::match(string){
    //~ cout << "Match a string" << endl;
//~ }

void Automata::synchronize(const Automata & other) {
    set<Transition*>::const_iterator it;
    //Saves a reference to each Transition
    for(it = other.transitions.begin();
        it != other.transitions.end();
        it++) {
        transitions.insert(*it);
        (*it)->reference();
    }
}

//---------- MEMORY STUFF -------------------------------------------
void Automata::delete_all() {
    for(set<Transition*>::const_iterator it = transitions.begin();
        it != transitions.end();
        it++) {
        if((*it)->dereference())
            delete *it;
    }
    transitions.clear();
}


//----------------- DISPLAY ------------------------------------
void Automata::mostrar(ostream & o) const {
    o << "----A:" << endl;
    set<Transition*>::const_iterator it;
    for(it = transitions.begin(); it != transitions.end(); it++) {
        o << "L: " << (*it)->label << endl;
        vector<Transition*>::const_iterator vit;
        for(vit = (*it)->next.begin(); vit != (*it)->next.end(); vit++) {
            o << "\t-->" << (*vit)->label << endl;
        }
    }
}

//------   Transition ---------------------

Automata::Transition::Transition(int cod): code(cod), count(1), label((cod == DOT)?'.':'/'){
    assert(cod != CHAR);
}


Automata::Transition::Transition(char w) : code(CHAR), count(1), label(w){}

void Automata::Transition::add_next(Transition* t){
    next.push_back(t);
}

bool Automata::Transition::dereference() {
    count--;
    return count == 0;
}

void Automata::Transition::reference() {
    count++;
}
