#include "automata.hpp"
#include <iostream>

using namespace std;

//Builds an empty automata
Automata::Automata() {

}
//Builds an alfanum automata
Automata::Automata(char){
    
}
//determinize the automata
void Automata::determinize(){
    
}

Automata & Automata::operator|(Automata & other){
    
    return *this;
}
//Concatenate two automata
Automata & Automata::operator+(Automata & other){
    
    return *this;
}
//Apply unary operator
Automata & Automata::apply_op(Automata & oper){
    
    return *this;
}

Automata & Automata::new_any() {
        Automata * res = new Automata();
        res->init = new Transition(DOT);
        return *res;
}

//Match a string
bool Automata::match(string){
    
}

Automata::Transition::Transition(int code){
    
}
Automata::Transition::Transition(char c){
    
}
void Automata::Transition::add_next(Transition & t){
    
}
