#ifndef AssignEdgeCost_H
#define AssignEdgeCost_H 
#include <lemon/list_graph.h>

void fill_cost_random(lemon::ListGraph::EdgeMap<double> *, lemon::ListGraph *, double );
void fill_cost_constant(lemon::ListGraph::EdgeMap<double> *, lemon::ListGraph *, double);
//Both functions assign costs to edges. 

#endif
