#ifndef __GREPLINE__
#define __GREPLINE__

#define YYSTYPE Automata
#define YYERROR_VERBOSE
#include "automata.hpp"


int yyparse();
int yylex (void);
void yyerror (char const *);
extern Automata automata;
#endif // __GREPLINE__
