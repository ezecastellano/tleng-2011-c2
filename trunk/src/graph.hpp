#ifndef __GRAPH__
#define __GRAPH__
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <iostream>


using namespace std;

/** The name for a State in the graph */
typedef unsigned int State;

/** The name for a dictionary pointing which states are reachable from a state
 * through a transition labeled with a char */
typedef map<char, set<State> > Trans;
/** Dstate is a Set of state, it is used when determinizing to name a new
 * D(eterministic)State */
typedef set<State> Dstate;
/** Syntatic sugar */
typedef Trans::const_iterator mit;

/** Labeled Directed Graph */
class LDGraph {
    
    public:
        /** Builds a automata that matches c.
         * if '.' is given matchs all.
         **/
        LDGraph(char c);
        
        /** This Graph is appended the other graph in a special way
         * such that it can match what it was matching or what the other was
         * matching.
         **/
        void operator |=(const LDGraph &);
        
        /** This Graph is appended the other graph in a special way
         * such that it can match what it was matching and then what the 
         * other was matching.
         **/
        void operator +=(const LDGraph &);
        
        
        LDGraph & operator =(const LDGraph &);
        
        /** Now this graph is allowed to match this or nothing 
         * (Through a lambda transition)*/
        void add_jump();
        
        /** Now this graph is allowed to match this many times
         * (Through a lambda transition)*/
        void add_inverse_jump();
        /** Determinize this LDGraph using the lambda-closure algorithm. */
        void determinize();
        
        //observers
        /** Returns the init State */
        State init() const;
        
        /** Returns true if the state is a final (accepted one) state */
        bool is_accepted(State state) const;
        /** Returns true if there is a transition from state that is labeled c. */
        bool can_move(State state, char c) const;
        
        /** Returns in res the states reachable from state through transitions 
         * labeled c. 
         **/
        void move_state(State state, char c, Dstate & res) const;
        
        void mostrar(ostream &) const;
        
    private:
    
        void move_dstate(const Dstate & dstate, Dstate &state, char c) const;
        void dtran(const Dstate & dstate, Dstate & res, char c) const;
        /* This method and the next one applyes lambda closure to a state
         * or a set of states */
        void lambda_closure_dstate(Dstate & dstate) const;
        void lambda_closure_state(State state, Dstate & res) const;
        
        /** returns a set of available transitions from a set of states */
        set<char> available_trans(const Dstate & s) const;
        
        /** Given a LDGraph, it appends all its states to this
         * renaming them with new ids. 
         * returns the id of the first state (they are numbered in order)*/
        unsigned int  copy_states(const LDGraph &);
        
        /* This method and following ones add a transition between one or 
         * many states. */
        void add_transition(State o, State d, char t);
        void add_transition(State o, Dstate d, char t);
        void add_transition(Dstate origins, State destiny, char t);
        void add_transition(Dstate origins, Dstate destinies, char t);
        
        //Fields
        vector< Trans > _rels;
        State _init;
        Dstate _tail;
        
    
    
};
ostream& operator<<(ostream & o, const LDGraph& g);
#endif //__GRAPH__

