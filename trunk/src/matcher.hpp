#ifndef __MATCHER__
#define __MATCHER__

#include <iostream>
#include <string>
#include "automata.hpp"

class Matcher {
        public:
            Matcher(Automata&);
            bool get_next_matched_line(istream& i, string & res);
        private:
            Automata automata;
};

#endif //__MATCHER__
