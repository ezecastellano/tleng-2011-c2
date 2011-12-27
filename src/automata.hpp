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
            Automata();
            
            Automata(char);
            
            void operator|=(Automata & other);
            //Concatenate two automata
            void operator+=(Automata & other);
            //Apply unary operator
            Automata & apply_op(const char cs);
            
            //Builds an anychar automata
            void determinize();
            //Match a string
            bool match(string);
            
            Automata & operator = (const Automata & other);
            
            void mostrar(ostream&) const;
            
            
            int id;
            
        protected:
            static int getId() { return global_id++; }
            
        private:
            static int global_id;
            LDGraph graph;
            
};

//~ int global_id = 0;

ostream& operator <<(ostream& o, const Automata & a);
#endif // __AUTOMATA__
