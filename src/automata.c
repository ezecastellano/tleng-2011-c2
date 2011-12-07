#include "automata.h"
#include <stdlib.h>

Automata build_automata() {
    State* init = (State*)malloc(sizeof(State));
    init->name = "init";
    return init;
}
