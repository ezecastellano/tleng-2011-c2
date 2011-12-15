
#define DOT 1
#define LAMBDA 2
#define END 3

typedef struct Transition Transition;
struct Transition
{
    /* This Transition name */
    int code;
    /* Links to another Transition */
    Transition** next;
    /* Amount of links */
    int next_size;
};

typedef struct Automata Automata;
struct Automata {
  Transition* init;
  Transition* tail;
};

/** Builds an empty automata */
Automata build_empty_automata();

/** */
Automata automata_handle_expression(Automata, char);

/** */
Automata concat_automatas(Automata, Automata);

Automata or_automatas(Automata, Automata);

Automata build_any_alfanum_automata();

Automata build_alfanum_automata(char);
/** Given an NDA returns a DA */
Automata determinize_automata(Automata);

/** Given an Automata and a string returns 1 if it matches*/
int follow(Automata, char* token);

Automata automata;
