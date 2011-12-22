#include "matcher.hpp"

Matcher::Matcher(Automata& a){
        automata = a;
}

char* Matcher::get_next_matched_line(istream& i){
    char* res = new char[2048];
    if(i.eof())
        return NULL;
    i.getline(res, 2048);
    bool matches = automata.match(res);
    while(not matches and not i.eof()) {
        i.getline(res, 2048);
        matches = automata.match(res);
    }
    res = (matches)?  res : NULL;
    if(res == NULL)
        delete res;
    return res;
}
