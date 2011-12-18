#ifndef __AUTOMATA__
#define __AUTOMATA__

#include <string>
#include <map>
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
            Automata & apply_op(const char cs);
            
            //Builds an anychar automata
            void determinize();
            //Match a string
            bool match(string);
            
            
            void mostrar(ostream&) const;
            
        private:
        
            //class State;
            
            //Call at end to remove all transitions
            void delete_all();
            
            // saves reference to the newly acquired Transitions
            void synchronize(const Automata &);
            
            
            class State {
                    public:
                        State();
                        
                        void add_next(State*  t, char c);
                        //memory stuff
                        bool dereference();
                        void reference();
                        
                        //fields
                        int count;
                        int id;
                        map< char , State* > next;
                        
                    private:
                        static int next_id;
                        
                        
            };
            State* init;
            State* tail;
            set<State*> states;
            
};
#endif // __AUTOMATA__
