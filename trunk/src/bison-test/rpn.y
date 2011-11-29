/* Reverse polish notation calculator.  */

%{
/* Esto es para definir el tipo de los terminales del parser */
#define YYSTYPE double
/*Librerias que voy a usar. */
#include <ctype.h>
#include <stdio.h>
/* esto está por que se necesitan declaradas antes de usarlas. */
int yylex (void);
void yyerror (char const *);
%}

/** Por cada terminal que sea más largo que un caracter lo declaramos como un 
token, aca son todos simbolos de una letra (+-*...) excepto por los numeros **/
%token NUM

%% /* Grammar rules and actions follow.  */


/* en esta gramatica hay 3 reglas: input, line y exp.
    Por el momento obvien los {}.
    Fijense que cada regla es el | (or) de parte derecha de reglas.
        input (el lenguaje) es una cadena vacia o agregar una line.
        line es un  enter o una exp  seguido de un enter.
        exp son las expresiones en notacion polaca inversa.
    Por ejemplo exp puede ser un NUM o puede ser un par de expresiones seguidas
    de un más: '1 1 * 2 +'.
    Luego lo que aparece entre {} es la expresion en C que se escribirá cuando
    se matchee satisfactoriamente esa regla.
    Fijense que se pueden hacer referencia a los elementos que parseamos con
    $n donde n es el numero de literal de la regla:
        exp exp '*'   { $$ = $1 * $2;      }
    y $$ es el nombre de la variable "resultado".
    
*/

input:    /* empty */
     | input line {printf("%s", $2);}
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


/* Algunos detalles:
    Sino me equivoco, es importante que 'input' este definido así y no al revés.
    Las reglas sin acciones, ejemplo line: '\n', lo que hacen es poner en $$, 
    el valor $1.
    
*/

/* The lexical analyzer returns a double floating point
        number on the stack and the token NUM, or the numeric code
        of the character read if not a number.  It skips all blanks
        and tabs, and returns 0 for end-of-input.  */

     
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
       return yyparse();
}

 /* Called by yyparse on error.  */
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}
