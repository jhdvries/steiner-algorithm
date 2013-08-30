#ifndef AssignConnectivityRequirement_H
#define AssignConnectivityRequirement_H
#include <lemon/list_graph.h>
#include <RequirementFunction.h>

void assign_connectivity_random(RequirementFunction *, lemon::ListGraph *, int);
void assign_connectivity_constant(RequirementFunction *, lemon::ListGraph *, int);
//Both functions Assign connectivty Requirement to every pair of nodes in the graph

#endif


