#ifndef __GRAPH__
#define __GRAPH__
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

//Labeled Directed Graph
class LDGraph {
    
    public:
        LDGraph(char c);
        void operator |=(const LDGraph &);
        void operator +=(const LDGraph &);
        
        //~ void add_prefix(char c);
        //~ void add_postfix(char c);
        void add_jump();
        void add_inverse_jump();
        void mostrar(ostream &) const;
        void dtran(set< int > dstate, set< int > &,  char c) const;
    
    private:
        void clausura_lambda_dstate(set<int> & dstate) const;
        void clausura_lambda_state(int state, set<int> & res) const;
        int move_state(int state, char c) const;
        bool can_move(int state, char c) const;
        void move_dstate(set<int> dstate, set<int> &state, char c) const;
        int copy_states(const LDGraph &);
        vector< map< char, int > > rels;
        int init;
        int tail;
        
    
    
};
ostream& operator<<(ostream & o, const LDGraph& g);
#endif //__GRAPH__

