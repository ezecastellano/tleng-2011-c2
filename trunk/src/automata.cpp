#include "automata.h"
#include <stdlib.h>
/* /: lambda
 */
 
Transition* new_transition(int code) {
    Transition* t = (Transition*)malloc(sizeof(Transition));
    t->code = code;
    t->next = NULL;
    t->next_size = 0;
    return t;
}

void add_transition(Transition* actual, Transition* t_next) {
    //Pido un arreglo de tamaño next_size + 1
    Transition** next = (Transition**)malloc(sizeof(Transition*) * (actual->next_size + 1));
    for(int i = 0; i < actual->next_size - 1; i++) {
        next[i] = actual->next[i];
    }
    
    next[actual->next_size] = t_next;
    free(actual->next);
    
    actual->next_size++;
    
}

Automata* build_lambda_automata() {
    // ^/$
    Automata* res = (Automata*)malloc(sizeof(Automata));
    Transition* t_lambda = new_transition(LAMBDA);
    Transition* tail = new_transition(END);
    res->init = t_lambda;
    res->tail = tail;
    
    return init;
}


/** */
Automata automata_handle_expression(Automata data, Automata ops, Automata rest)
{
    }

/** */
Automata concat_automatas(Automata binary, Automata other)
{
    }

Automata build_any_alfanum_automata(){
    }

Automata build_alfanum_automata(char c){
    }
/** Given an NDA returns a DA */
Automata determinize_automata(Automata a)
{
    }
/** Given a Transition and a token it returns the Transition after following that token */
Automata follow(Automata a, char* token)
{
    }
