#ifndef __AUTOMATA__
#define __AUTOMATA__

#include <string>
#include <map>
#include <set>
#include "graph.hpp"

#define DOT 1
#define LAMBDA 2
#define CHAR 3

using namespace std;

class Automata {
        public:
            /** Builds an empty automata (matchs anything) */
            Automata();
            
            /** Build a new automata that matches a char (or every char if '.'
             * is given */
            Automata(char);
            
            /** This automata now match what it was matching or the other 
             * automata */
            void operator|=(Automata & other);
            /** Concatenate two automata */
            void operator+=(Automata & other);
            /** Apply unary operator like '*', '+' and  '?' */
            Automata & apply_op(const char cs);
            
            /** Convert this automata from NDA to DFA */
            void determinize();
            /** Given a string answer if this Automataaa matches it
             * Must be a DFA Automata (apply determinize)*/
            bool match(string);
            
            
            Automata & operator = (const Automata & other);
            
            void mostrar(ostream&) const;
            
            
        private:
            LDGraph graph;
            
};

ostream& operator <<(ostream& o, const Automata & a);
#endif // __AUTOMATA__
