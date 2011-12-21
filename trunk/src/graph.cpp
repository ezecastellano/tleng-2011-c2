#include "graph.hpp"
#include <cassert>

using namespace std;

#define INIT 1
#define TAIL 2
typedef map<char, int>::const_iterator mit;
LDGraph::LDGraph(char c) : rels(2) {
    init = 0;
    tail = 1;
    rels[init][c] = 1;
}



void LDGraph::operator |=(const LDGraph & other){
    if(this == &other)
        return;
    int offset = copy_states(other);
    rels[init]['/'] = other.init + offset;
    rels[other.tail + offset]['/'] = tail;
}

void LDGraph::operator +=(const LDGraph & other){
    int offset = copy_states(other);
    rels[tail]['/'] = offset + other.tail;
    tail = offset + other.tail;
}

int LDGraph::copy_states(const LDGraph & other) {
    unsigned int offset = rels.size();
    unsigned int osize = other.rels.size();
    rels.resize(other.rels.size() + offset);
    for(unsigned int i = 0; i < osize; i++) {
        map < char, int> actual = other.rels[i];
        for(mit it = actual.begin(); it != actual.end(); it++) {
            char k = it->first;
            int v = it->second + offset;
            rels[offset + i][k] = v;
        }
    }
    return offset;
}

void LDGraph::add_jump(){
    rels[init]['/'] = tail;
}

void LDGraph::add_inverse_jump(){
    rels[tail]['/'] = init;
}

void LDGraph::dtran(set< int > dstate, set<int> & res, char c) const {
    move_dstate(dstate, res, c);
    clausura_lambda_dstate(res);
}

void LDGraph::clausura_lambda_dstate(set<int> & dstate) const {
        for(set< int >::iterator it = dstate.begin();
            it != dstate.end();
            it++) {
            clausura_lambda_state(*it, dstate);
        }
}
void LDGraph::clausura_lambda_state(int state, set<int> & res) const {
    res.insert(state);
    for(mit it = rels[state].begin(); it != rels[state].end(); it++){
        if(it->first == '/' and not res.count(it->second))
            clausura_lambda_state(it->second, res);
    }
}
int LDGraph::move_state(int state, char c) const {
    assert(can_move(state, c));
    return rels[state].find(c)->second;
}

bool LDGraph::can_move(int state, char c) const {
    return rels[state].count(c);
}
void LDGraph::move_dstate(set<int> dstate, set<int> &res, char c) const {
    for(set< int >::iterator it = dstate.begin();
            it != dstate.end();
            it++) {
        if(can_move(*it, c))
            res.insert(move_state(*it, c));
    }
}

void LDGraph::mostrar(ostream & o) const {
    o << "----" << endl;
    
    for(unsigned int i = 0; i < rels.size(); i++) {
        mit it;
        o << i << endl;
        for(it = rels[i].begin(); 
            it != rels[i].end();
            it++) {
            o << i;
            o << " -> ";
            o << it->second;
            o << "[ label=\"";
            o << it->first;
            o << "\"]" << endl;
        }
    }
}


ostream& operator<<(ostream & o, const LDGraph& g) {
    g.mostrar(o);
    return o;
}




