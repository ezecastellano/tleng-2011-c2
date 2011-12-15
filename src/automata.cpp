#include "automata.hpp"

//Builds an empty automata
Automata::Automata() {
    
}
//Builds an alfanum automata
Automata::Automata(char){
    
}
//determinize the automata
void Automata::determinize(){
    
}

Automata Automata::operator|(Automata & other){
    
}
//Concatenate two automata
Automata Automata::operator+(Automata & other){
    
}
//Apply unary operator
Automata Automata::apply_op(char){
    
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
