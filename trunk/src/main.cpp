#include "define.hpp"
#include "automata.hpp"
#include "grep-line.tab.hpp"
#include <stdio.h>
#include <ctype.h>
#include <error.h>
#include <string.h>
#include <iostream>

using namespace std;

char* regexp;
int regexp_index = 0;

char get_next() {
    char c = regexp[regexp_index];
    regexp++;
    return c;
}

 /* Called by yyparse on error.  */
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}

int yylex (void) {
    char c = get_next();
    cout << "lex = " << c << endl;
    /* END */
    if (c == EOF)
        return 0;
        
    /* Process ALFANUM.  */
    if (isalpha(c) || isdigit (c) || c == ' ' ) {
        yylval = Automata(c);
        return ALFANUM;
    }
    /* Return a single char.  */
    return c;
}

int main (int argc, char * argv[]) {
        if( argc < 2 || argc == 3 || (argc == 4 && strcmp(argv[2], "-f"))) {
            error(2, 0, "Missing argument.\nUsage: %s regexp [-f file]", argv[0]);
        }
        regexp = argv[1];
        printf("Regexp: %s\n", regexp);
        if(argc > 2) {
            printf("Should parse this file %s\n", argv[3]);
        }
        //~ build_automata();
        if(yyparse()) {
            cout << "Regexp no fue parseada correctamente." << endl;
        }
        //Por cada linea de texto, imprimirla si matchea con el automata
        return 0;
}
