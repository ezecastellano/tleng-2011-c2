#include "define.hpp"
#include "automata.hpp"
#include "grep-line.tab.hpp"
#include "matcher.hpp"
#include <stdio.h>
#include <ctype.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

char* regexp;
int regexp_index = 0;
Automata automata;

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
    /* END */
    if (c == EOF)
        return 0;
        
    /* Process ALFANUM.  */
    if (isalnum(c) || c == ' ' ) {
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
        if(yyparse()) {
            cout << "Regexp no fue parseada correctamente." << endl;
        }
        ifstream f;
        streambuf * rdbuf = cin.rdbuf();
        if(argc > 2) {
            cout << "Should parse this file: " << argv[3] << endl;
            f.open(argv[3]);
            rdbuf = f.rdbuf();
        }
        istream in(rdbuf);
        Matcher m(automata);
        string out;
        while(m.get_next_matched_line(in, out))
            cout << out << endl;
        return 0;
}
