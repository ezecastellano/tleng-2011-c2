#ifndef __MATCHER__
#define __MATCHER__

#include <iostream>
#include <string>
#include "automata.hpp"

class Matcher {
        public:
            /** Builds a matcher from an automata */
            Matcher(Automata&);
            /** Given a istream, it returns true or false if there's a line which
             * matches with the Automata provided at the constructions, and returns
             * in res the given line. */
            bool get_next_matched_line(istream& i, string & res);
        private:
            Automata automata;
};

#endif //__MATCHER__
