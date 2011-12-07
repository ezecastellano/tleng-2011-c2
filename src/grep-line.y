/* Reverse polish notation calculator.  */

%{
#include "define.h"
#include "automata.h"
/*Librerias que voy a usar. */
#include <ctype.h>
#include <stdio.h>
%}

%token NUM

%% /* Grammar rules and actions follow.  */

input:    /* empty */
     | input line
;

line:     '\n'
     | exp '\n'      { printf ("Res:\t%.10g\n", $1); }
;

exp:      NUM           { $$ = $1;           }
     | exp exp '+'   { $$ = $1 + $2;      }
     | exp exp '-'   { $$ = $1 - $2;      }
     | exp exp '*'   { $$ = $1 * $2;      }
     | exp exp '/'   { $$ = $1 / $2;      }
      /* Exponentiation */
      /* Unary minus, lo declararon como un n de negativo para evitar aambiguedad con el - */
     | exp 'n'       { $$ = -$1;          }
;
%%


int yylex (void) {
    int c;

    /* Skip white space.  */
    while ((c = getchar ()) == ' ' || c == '\t')
     ;
    /* Process numbers.  */
    if (c == '.' || isdigit (c)) {
       ungetc(c, stdin);
       scanf("%lf", &yylval);
       return NUM;
    }
    /* Return end-of-input.  */
    if (c == EOF)
     return 0;
    /* Return a single char.  */
    return c;
}
     
     
int main (void) {
        build_automata();
        return yyparse();
}

 /* Called by yyparse on error.  */
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}
