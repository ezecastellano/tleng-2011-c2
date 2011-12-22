#ifndef __GRAPH__
#define __GRAPH__
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <iostream>


using namespace std;

typedef unsigned int State;
typedef map<char, set<State> > Trans;
typedef Trans::const_iterator mit;
typedef set<State> Dstate;

//Labeled Directed Graph
class LDGraph {
    
    public:
        LDGraph(char c);
        void operator |=(const LDGraph &);
        void operator +=(const LDGraph &);
        
        void add_jump();
        void add_inverse_jump();
        void mostrar(ostream &) const;
        void determinize();
        bool can_move(State state, char c) const;
    private:
        void dtran(const Dstate & dstate, Dstate & res, char c) const;
        void clausura_lambda_dstate(Dstate & dstate) const;
        void clausura_lambda_state(State state, Dstate & res) const;
        void move_state(State state, char c, Dstate &) const;
        void move_dstate(const Dstate & dstate, Dstate &state, char c) const;
        unsigned int  copy_states(const LDGraph &);
        set< char> available_trans(const Dstate & s);
        void add_transition(State o, State d, char t);
        void add_transition(State o, Dstate d, char t);
        void add_transition(Dstate origins, State destiny, char t);
        void add_transition(Dstate origins, Dstate destinies, char t);
        
        //Fields
        vector< Trans > rels;
        State init;
        Dstate tail;
        
    
    
};
ostream& operator<<(ostream & o, const LDGraph& g);
#endif //__GRAPH__

