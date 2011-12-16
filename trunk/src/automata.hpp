#ifndef __AUTOMATA__
#define __AUTOMATA__

#include <string>
#include <vector>
#define DOT 1
#define LAMBDA 2
#define CHAR 3

using namespace std;

class Automata {
        public:
            Automata();
            Automata(const Automata&);
            //Builds an alfanum automata
            Automata(char);
            
            //Builds an anychar automata
            static Automata & new_any();
            //determinize the automata
            void determinize();
            
            Automata & operator|(Automata & other);
            //Concatenate two automata
            Automata & operator+(Automata & other);
            //Apply unary operator
            Automata & apply_op(Automata&);
            
            //Match a string
            bool match(string);
            
        private:
            class Transition {
                    public:
                        Transition(int code);
                        Transition(char c);
                        void add_next(Transition*  t);
                        char c;
                    private:
                        int code;
                        vector<Transition*> next;
                        
            };
            Transition* init;
            Transition* tail;
            
};
#endif // __AUTOMATA__
