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
   fprintf (stderr, "%s", s);
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
        string out;
        if( argc < 2 ) {
            error(2, 0, "Missing argument.\nUsage:\t%s regexp [file] [-i]\n\n\t%s regexp\t: Reads and match text from stdin\n\t%s regexp file\t: Reads and match text from file\n\t-i \t: Makes a graphviz dot file with the automata obtained from the given regular expression.", argv[0], argv[0], argv[0]);
        }
        regexp = argv[1];
        cerr << "Regexp: \"" << regexp << "\"" << endl;
        //Match regular expression and build automata.
        if(yyparse()) {
            error(2, 0, "Regexp no fue parseada correctamente: \"%s\"", argv[1]);
        }
        
        //Automata should be determinized.
        automata.determinize();
        
        //If -i option is given saves the automata generated by this regex
        if(argc > 3 && not strcmp(argv[3], "-i")) {
            ofstream g("grep-line.dot");
            automata.mostrar(g);
            g.close();
        }
        
        //Where to read from
        streambuf * rdbuf = cin.rdbuf();
        ifstream f;
        if(argc > 2) {
            cerr << "Archivo a parsear: " << argv[2] << endl;
            f.open(argv[2]);
            if(not f.good()) {
                error(2, 0, "File does not exist or can not read from \"%s\"", argv[2]);
            }
            rdbuf = f.rdbuf();
        }
        istream in(rdbuf);
        
        Matcher m(automata);
        cerr << "Matched lines:" << endl;
        //For each matched line
        while(m.get_next_matched_line(in, out))
            cout << out << endl;
        return 0;
}
