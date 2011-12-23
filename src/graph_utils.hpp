#ifndef __GRAPH_UTILS__
#define __GRAPH_UTILS__

#include "graph.hpp"

State find(vector< Dstate > & dstates, const Dstate & s);
Dstate find_or_create(   vector< Dstate > & dstates, 
                        vector< Trans > & relations, 
                        stack < State > & pending_dstates,
                        Dstate & s);
Dstate offset_dstates(Dstate states, int offset);
ostream& operator <<(ostream& o, const Dstate & d);
void print_dstate_trans(Dstate & s, Dstate & d, char c);                    
bool set_match(const Dstate one, const Dstate two);
void add_to_tail(const Dstate & n, Dstate & new_tail, const Dstate & old_tail, State new_state);


#endif // __GRAPH_UTILS__
