#ifndef __MATCHER__
#define __MATCHER__

#include <iostream>

class Matcher {
        public:
            Matcher(Automata&, istream&);
            string * get_next_matched_line();
        private:
            Automata a;
            istream in;
}

#endif //__MATCHER__
