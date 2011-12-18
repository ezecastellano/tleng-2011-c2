#include "automata.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <execinfo.h>

using namespace std;

Automata::Automata() : init(NULL), tail(NULL) { }

Automata::~Automata() {
    init = NULL;
    tail = NULL;
    delete_all();
}


Automata & Automata::operator = (const Automata & other) {
    cout << "Call operator =" << endl;
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
    init = new State();
    tail = new State();
    init->add_next(tail, c);
    states.insert(init);
    states.insert(tail);
}

//determinize the automata
void Automata::determinize(){
    cout << "Determinize" << endl;
}

// ---------------  operators ----------------------------------------

Automata & Automata::operator|(Automata & other){
    State* new_init = new State();
    State* new_tail = new State();
    //Fork
    new_init->add_next(other.init, '/');
    new_init->add_next(init, '/');
    //Join
    other.tail->add_next(new_tail, '/');
    tail->add_next(new_tail, '/');
    //rename
    init = new_init;
    tail = new_tail;
    
    //memory managment
    states.insert(new_init);
    states.insert(new_tail);
    synchronize(other);
    return *this;
}
//Concatenate two automata
Automata & Automata::operator+(Automata & other){
    //Bind
    tail->add_next(other.init, '/');
    tail = other.tail;
    
    //MM
    synchronize(other);
    return *this;
}

//Apply unary operator
Automata & Automata::apply_op(const char c){
    State* new_init = new State();
    State* new_tail = new State();
    
    // Extend with lambda
    new_init->add_next(init, '/');
    tail->add_next(new_tail, '/');
    
    if(c == '?' || c == '*'){
        // Enable not to match this automata.
        new_init->add_next(new_tail, '/');
    } 
    
    if (c == '+' || c == '*'){
        // Enable to match  this automata many times.(self loop)
        tail->add_next(init, '/');
    }
    
    init = new_init;
    tail = new_tail;
    
    states.insert(init);
    states.insert(tail);
    
    return *this;
}

//Match a string
bool Automata::match(string){
    cout << "Match a string" << endl;
    return true;
}

//---------- MEMORY STUFF -------------------------------------------
void Automata::synchronize(const Automata & other) {
    set<State*>::const_iterator it;
    //Saves a reference to each State
    for(it = other.states.begin();
        it != other.states.end();
        it++) {
        states.insert(*it);
        (*it)->reference();
    }
}

void Automata::delete_all() {
    for(set<State*>::const_iterator it = states.begin();
        it != states.end();
        it++) {
        if((*it)->dereference())
            delete *it;
    }
    states.clear();
}


//----------------- DISPLAY ------------------------------------
void Automata::mostrar(ostream & o) const {
    o << "----" << endl;
    set<State*>::const_iterator it;
    for(it = states.begin(); it != states.end(); it++) {
        //~ o << "L: " << (*it)->label << endl;
        map<char, State*>::const_iterator vit;
        //~ for(vit = (*it)->next.begin(); vit != (*it)->next.end(); vit++) {
            //~ o << "\t-->" << (*vit)->label << endl;
        //~ }|
    }
}

//------   State ---------------------
int Automata::State::next_id = 0;

Automata::State::State() {
    id = next_id++;
}

                        
void Automata::State::add_next(State*  t, char c){
    next[c] = t;
}

bool Automata::State::dereference() {
    count--;
    return count == 0;
}

void Automata::State::reference() {
    count++;
}

