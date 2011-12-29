#ifndef __GRAPH_UTILS__
#define __GRAPH_UTILS__

#include "graph.hpp"

/** Returns the position of the state s in the vector dstates or
 * dstates.size() otherwise
 */
State find(vector< Dstate > & dstates, const Dstate & s);

/** Returns the position of s in dstates,
 * it adds s to dstates, resize relations by one
 * and push s to the stack if s wasn't in the vector.
 */
Dstate find_or_create(   vector< Dstate > & dstates, 
                        vector< Trans > & relations, 
                        stack < State > & pending_dstates,
                        Dstate & s);
/** Returns a new set where each state is an offset of each state in Dstate  */
Dstate offset_dstates(Dstate states, int offset);


/** Adds the new_state to the new_tail only if n has a state in the old_tail */
void add_to_tail(const Dstate & n, Dstate & new_tail, const Dstate & old_tail, State new_state);


#endif // __GRAPH_UTILS__
