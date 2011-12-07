
typedef struct State State;
struct State
{
    /* This state name */
    char* name;
    /* Links to another state */
    State** next;
    /* Amount of links */
    int next_size;
};
typedef State* Automata;

/** Builds an empty automata */
Automata build_automata();
/** Given an NDA returns a DA */
Automata determinize_automata(Automata);
/** Given a State and a token it returns the State after following that token */
State* follow(State *, char* token);
