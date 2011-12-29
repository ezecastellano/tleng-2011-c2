#include "graph_utils.hpp"

/** Returns true if intersection is not empty */
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

Dstate offset_dstates(Dstate states, int offset) {
    Dstate res;
    for(Dstate::iterator it = states.begin(); it != states.end(); it++)
        res.insert(*it + offset);
    return res;
}
