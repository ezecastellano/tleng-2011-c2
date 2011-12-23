#include "graph.hpp"
#include "graph_utils.hpp"
#include <cassert>
#include <stack>
#include <initializer_list>
#include <algorithm>

using namespace std;



#define INIT 0
#define TAIL 1

LDGraph::LDGraph(char c) : _rels(2) {
    _init = INIT;
    _tail = Dstate({TAIL});
    if( c == '.') {
        //Graph does not support '.' transition as is
        for( char b = '0'; b < '9' + 1; b++) {
            add_transition(INIT, TAIL, b);
        }
        for( char b = 'A'; b < 'Z' + 1; b++) {
            add_transition(INIT, TAIL, b);
        }
        for( char b = 'a'; b < 'z' + 1; b++) {
            add_transition(INIT, TAIL, b);
        }
    } else {
        add_transition(INIT, TAIL, c);
    }
}



void LDGraph::operator |=(const LDGraph & other){
    if(this == &other)
        return;
    int offset = copy_states(other);
    add_transition(_init, other._init + offset, '/');
    add_transition(offset_dstates(other._tail, offset), _tail, '/');
}

void LDGraph::operator +=(const LDGraph & other){
    unsigned int offset = copy_states(other);
    add_transition(_tail, other._init + offset,  '/');
    _tail = offset_dstates(other._tail, offset);;
}


unsigned int LDGraph::copy_states(const LDGraph & other) {
    unsigned int offset = _rels.size();
    unsigned int osize = other._rels.size();
    _rels.resize(osize + offset);
    for(unsigned int i = 0; i < osize; i++) {
        Trans actual = other._rels[i];
        for(mit it = actual.begin(); it != actual.end(); it++) {
            char k = it->first;
            for(Dstate::iterator sit = it->second.begin();
                sit != it->second.end();
                sit++) {
                int v = *sit + offset;
                add_transition(i + offset, v, k);
            }
        }
    }
    return offset;
}

void LDGraph::add_jump(){
    add_transition(_init, _tail, '/');
}

void LDGraph::add_inverse_jump(){
    add_transition(_tail, _init, '/');
}

void LDGraph::add_transition(State origin, State destiny, char t) {
    _rels[origin][t].insert(destiny);
}

void LDGraph::add_transition(State origin, Dstate destinies, char t) {
    for(Dstate::iterator it = destinies.begin(); it != destinies.end(); it++)
        add_transition(origin, *it, t);
}

void LDGraph::add_transition(Dstate origins, State destiny, char t) {
    for(Dstate::iterator it = origins.begin(); it != origins.end(); it++)
        add_transition(*it, destiny, t);
}

void LDGraph::add_transition(Dstate origins, Dstate destinies, char t) {
    for(Dstate::iterator it = origins.begin(); it != origins.end(); it++)
        add_transition(*it, destinies, t);
}

void LDGraph::dtran(const Dstate & dstate, Dstate & res, char c) const {
    move_dstate(dstate, res, c);
    clausura_lambda_dstate(res);
}

void LDGraph::clausura_lambda_dstate(Dstate & dstate) const {
    for(set< State >::iterator it = dstate.begin();
        it != dstate.end();
        it++) {
        clausura_lambda_state(*it, dstate);
    }
}
void LDGraph::clausura_lambda_state(State state, Dstate & res) const {
    res.insert(state);
    for(mit it = _rels[state].begin(); it != _rels[state].end(); it++){
        if(it->first == '/' )
            for( set<State>::const_iterator sit = it->second.begin();
                 sit != it->second.end();
                 sit++) {
                if(not res.count(*sit))
                    clausura_lambda_state(*sit, res);
            }
    }
}
void LDGraph::move_state(State state, char c, Dstate & res) const {
    //assert(can_move(state, c));
    Dstate follow = _rels[state].find(c)->second;
    for( Dstate::iterator dit = follow.begin();
        dit != follow.end();
        dit++) {
        res.insert(*dit);
    }
        
    return ;
}

bool LDGraph::can_move(State state, char c) const {
    return _rels[state].count(c);
}
void LDGraph::move_dstate(const Dstate & dstate, Dstate & res, char c) const {
    assert(c != '/');
    for(Dstate::const_iterator it = dstate.begin();
            it != dstate.end();
            it++) {
        if(can_move(*it, c))
            move_state(*it, c, res);
    }
}

set< char> LDGraph::available_trans(const Dstate & s) const {
    set<char> res;
    for(Dstate::const_iterator st = s.begin(); st != s.end(); st++) {
        Trans m = _rels[*st];
        for(mit it = m.begin(); it != m.end(); it++) {
            if(it->first != '/')
                res.insert(it->first);
        }
    }
    return res;
}

State LDGraph::init() const {
    return _init;
}

bool LDGraph::is_accepted(State t) const {
    return _tail.count(t);
}



void LDGraph::determinize() {
    Dstate initial({_init});
    clausura_lambda_dstate(initial);
    vector< Dstate > dstates({initial});
    vector< Trans > relations(1);
    stack< State > pending_dstates( {0} );
    Dstate new_tail;
    while( not pending_dstates.empty() ) {
        // pop pending set of states to determinize.
        State d = pending_dstates.top();
        pending_dstates.pop();
        //For each available transition
        set<char> chars = available_trans(dstates[d]);
        for(set<char>::iterator chs = chars.begin(); chs != chars.end(); chs++) {
            Dstate s;
            //Apply Dtran(A, c) A = set of states; c = transition;
            dtran(dstates[d], s, *chs);
            // Save the translation of this new state.
            relations[d][*chs] = find_or_create(dstates, relations, pending_dstates, s);
        }
        //IF this state contains a end state, i'll add it to the end.
        add_to_tail(dstates[d], new_tail, _tail, d);
    }
    _rels = relations;
    _tail = new_tail;
}


void LDGraph::mostrar(ostream & o) const {
    o << "digraph  {" << endl;
    for(unsigned int i = 0; i < _rels.size(); i++) {
        o << i;
        o << ((i == _init)? "[ label=\"Init\" ]" : " ");
        o << ((_tail.count(i))? "[ label=\"Tail\" ]" : " ");
        o << endl;
        mit it;
        for(it = _rels[i].begin(); 
            it != _rels[i].end();
            it++) {
            for( Dstate::iterator sit = it->second.begin();
                sit != it->second.end();
                sit++) {
                o << i;
                o << " -> ";
                o << *sit;
                o << "[ label=\"";
                o << it->first;
                o << "\" ]" << endl;
            }
        }
    }
    o << '}' << endl;
}


ostream& operator<<(ostream & o, const LDGraph& g) {
    g.mostrar(o);
    return o;
}




