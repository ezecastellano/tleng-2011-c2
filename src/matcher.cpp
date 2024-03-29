#include "matcher.hpp"
#include <string>

Matcher::Matcher(Automata& a){
        automata = a;
}

bool Matcher::get_next_matched_line(istream& i, string & res){
    bool matches = false;
    i.peek();
    while(not matches and i.good()) {
        getline(i, res);
        matches = automata.match(res);
    }
    return matches;
}
