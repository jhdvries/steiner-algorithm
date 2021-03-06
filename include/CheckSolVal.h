#ifndef CheckSolVal_H
#define CheckSolVal_H
#include <lemon/list_graph.h>

//check for seeing if a certain value is in the solution, the boolean at the end is for 1 if we look for an integer value specifically not relevant for F[e]=1
bool check_sol_val(lemon::ListGraph *, lemon::ListGraph::EdgeMap<double> *, lemon::ListGraph::EdgeMap<int> *, double, double, bool);

//input is graph, solution "map" with fractional values, an upper and a lower bound and a boolean
#endif

