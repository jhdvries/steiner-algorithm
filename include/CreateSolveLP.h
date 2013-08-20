#ifndef CreateSolveLP_H
#define CreateSolveLP_H
#include <lemon/list_graph.h>
#include <AssignConnectivityRequirement.h>
#include <RequirementFunction.h>
#include <iostream>
#include <lemon/glpk.h>
#include <lemon/lp.h>
#include "SourceTargetArc.h"



//This function has input of the graph, the value y of the variables, the costs of the edges, the requirement on V*V and an edge to fix and a bool to say whether something needs to be fixed or not
void solve_lp(lemon::ListGraph *,lemon::ListGraph::EdgeMap<double> *,lemon::ListGraph::EdgeMap<int> *, RequirementFunction*, lemon::ListGraph::EdgeMap<int> *, lemon::ListGraph::Edge *, double*, bool );    

// it should solve the LP and adjust y to represent the changed value of the variables after solving the LP
// Also it should occasionally fix some variables to try if the value is the same

#endif


