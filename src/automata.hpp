#ifndef __AUTOMATA__
#define __AUTOMATA__

#include <string>
#include <vector>
#include <set>
#define DOT 1
#define LAMBDA 2
#define CHAR 3

using namespace std;

class Automata {
        public:
            Automata();
            //Builds an alfanum automata
            Automata(char);
            // Destroys this automata and dereference its transition
            ~Automata();
            // Copy constructor
            Automata(const Automata&);
            // operator =
            Automata & operator =(const Automata &);
            
            Automata & operator|(Automata & other);
            //Concatenate two automata
            Automata & operator+(Automata & other);
            //Apply unary operator
            Automata & apply_op(Automata&);
            
            //Builds an anychar automata
            void determinize();
            //Match a string
            bool match(string);
            
            
            void mostrar(ostream&) const;
            
        private:
        
            class Transition;
            
            //Call at end to remove all transitions
            void delete_all();
            
            // saves reference to the newly acquired Transitions
            void synchronize(const Automata &);
            
            
            class Transition {
                    private:
                            int code;
                            int count;
                    public:
                        Transition(int code);
                        Transition(char c);
                        char label;
                        vector<Transition*> next;
                        
                        void add_next(Transition*  t);
                        bool dereference();
                        void reference();
                        
            };
            Transition* init;
            Transition* tail;
            set<Transition*> transitions;
            
};
#endif // __AUTOMATA__
