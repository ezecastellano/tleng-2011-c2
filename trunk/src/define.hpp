#ifndef __GREPLINE__
#define __GREPLINE__
#define YYSTYPE Automata

#define YYERROR_VERBOSE

int yyparse();
int yylex (void);
void yyerror (char const *);
#endif // __GREPLINE__
