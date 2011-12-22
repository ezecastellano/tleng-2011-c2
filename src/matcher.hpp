#ifndef __MATCHER__
#define __MATCHER__

#include <iostream>
#include <string>
#include "automata.hpp"

class Matcher {
        public:
            Matcher(Automata&);
            char* get_next_matched_line(istream&);
        private:
            Automata automata;
};

#endif //__MATCHER__
