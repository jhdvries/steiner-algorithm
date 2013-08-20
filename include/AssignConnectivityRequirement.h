#ifndef AssignConnectivityRequirement_H
#define AssignConnectivityRequirement_H
#include <lemon/list_graph.h>
#include <RequirementFunction.h>

void assign_connectivity_random(RequirementFunction *, lemon::ListGraph *);
void assign_connectivity_constant(RequirementFunction *, lemon::ListGraph *);
//void fill_cost_difference(lemon::ListGraph::EdgeMap<int> *, lemon::ListGraph *);
#endif


