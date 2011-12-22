#include "graph.hpp"
#include <cassert>
#include <stack>
#include <initializer_list>
#include <algorithm>

using namespace std;
/** Helpers **/

ostream& operator <<(ostream& o, const Dstate & d) {
    o << '[';
    for(Dstate::iterator i = d.begin(); i != d.end(); i++)
    {
        o << ((i != d.begin())? ", " : " ");
        o << *i;
    }   
    o << " ]";
    return o;
}

#define INIT 0
#define TAIL 1

LDGraph::LDGraph(char c) : rels(2) {
    init = INIT;
    tail = Dstate({TAIL});
    if( c == '.') {
        //Graph does not support '.' transition
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

Dstate offset_dstates(Dstate states, int offset) {
    Dstate res;
    for(Dstate::iterator it = states.begin(); it != states.end(); it++)
        res.insert(*it + offset);
    return res;
}

void LDGraph::operator |=(const LDGraph & other){
    if(this == &other)
        return;
    int offset = copy_states(other);
    add_transition(init, other.init + offset, '/');
    add_transition(offset_dstates(other.tail, offset), tail, '/');
}

void LDGraph::operator +=(const LDGraph & other){
    unsigned int offset = copy_states(other);
    add_transition(tail, other.init + offset,  '/');
    tail = offset_dstates(other.tail, offset);;
}


unsigned int LDGraph::copy_states(const LDGraph & other) {
    unsigned int offset = rels.size();
    unsigned int osize = other.rels.size();
    rels.resize(other.rels.size() + offset);
    for(unsigned int i = 0; i < osize; i++) {
        Trans actual = other.rels[i];
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
    add_transition(init, tail, '/');
}

void LDGraph::add_inverse_jump(){
    add_transition(tail, init, '/');
}

void LDGraph::add_transition(State origin, State destiny, char t) {
    rels[origin][t].insert(destiny);
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
    for(mit it = rels[state].begin(); it != rels[state].end(); it++){
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
    Dstate follow = rels[state].find(c)->second;
    for( Dstate::iterator dit = follow.begin();
        dit != follow.end();
        dit++) {
        res.insert(*dit);
    }
        
    return ;
}

bool LDGraph::can_move(State state, char c) const {
    return rels[state].count(c);
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

set< char> LDGraph::available_trans(const Dstate & s) {
    set<char> res;
    for(Dstate::const_iterator st = s.begin(); st != s.end(); st++) {
        Trans m = rels[*st];
        for(mit it = m.begin(); it != m.end(); it++) {
            if(it->first != '/')
                res.insert(it->first);
        }
    }
    return res;
}

State find(vector< Dstate > & dstates, const Dstate & s){
    for(State j = 0; j < dstates.size(); j++) {
        if( dstates[j].size() == s.size() 
            and equal(dstates[j].begin(), dstates[j].end(), s.begin()))
            return j;
    }
    return dstates.size();
}

Dstate find_or_create(   vector< Dstate > & dstates, 
                        vector< Trans > & relations, 
                        stack < State > & pending_dstates,
                        Dstate & s) {
    State follow = find(dstates, s);
    if(follow >= dstates.size()) {
        //Mark state as checked
        dstates.push_back(s);
        follow = dstates.size() - 1;
        pending_dstates.push(follow);
        relations.resize(relations.size() + 1);
    }
    return Dstate({follow});
}

void print_dstate_trans(Dstate & s, Dstate & d, char c) {
    cerr << s << " -- " << c << " --> " << d << endl;
}

bool set_match(const Dstate one, const Dstate two) {
    for( Dstate::const_iterator it = one.begin();
        it != one.end();
        it++) {
        if(two.count(*it))
            return true;
    }
    return false;
        
}
void add_to_tail(const Dstate & n, Dstate & new_tail, const Dstate & old_tail, State new_state) {
    if( set_match(n,old_tail) )
        new_tail.insert(new_state);
    return;
}


void LDGraph::determinize() {
    Dstate initial({init});
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
        add_to_tail(dstates[d], new_tail, tail, d);
    }
    rels = relations;
    tail = new_tail;
}


void LDGraph::mostrar(ostream & o) const {
    cout << "digraph  {" << endl;
    for(unsigned int i = 0; i < rels.size(); i++) {
        o << i;
        o << ((i == init)? "[ label=\"Init\" ]" : " ");
        o << ((tail.count(i))? "[ label=\"Tail\" ]" : " ");
        o << endl;
        mit it;
        for(it = rels[i].begin(); 
            it != rels[i].end();
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
    cout << '}' << endl;
}


ostream& operator<<(ostream & o, const LDGraph& g) {
    g.mostrar(o);
    return o;
}




