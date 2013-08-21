#ifndef AssignEdgeCost_H
#define AssignEdgeCost_H 
#include <lemon/list_graph.h>

void fill_cost_random(lemon::ListGraph::EdgeMap<double> *, lemon::ListGraph *, double );
void fill_cost_constant(lemon::ListGraph::EdgeMap<double> *, lemon::ListGraph *, double);
//void fill_cost_difference(lemon::ListGraph::EdgeMap<int> *, lemon::ListGraph *);
#endif
