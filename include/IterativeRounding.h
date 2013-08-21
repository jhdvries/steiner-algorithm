#ifndef ITERATIVEROUNDING_H
#define ITERATIVEROUNDING_H
#include <iostream>
#include <lemon/list_graph.h>
#include "GenerateGraph.h"
#include "AssignEdgeCost.h"
#include "AssignConnectivityRequirement.h"
#include "RequirementFunction.h"
#include "CreateSolveLp.h"
#include "CheckSolVal.h"


// 
void iterative_rounding(lemon::ListGraph * , lemon::ListGraph::EdgeMap<double> * , RequirementFunction * , lemon::ListGraph::EdgeMap<double> * , 
    lemon::ListGraph::EdgeMap<double> * , double * , double * );

// input is 
//1 the graph G,
//2 the Cost edgemap
//3 the nodepair requirement function
//4 An empty EdgeMap which will contain the values of the solution x
//5 An empty EdgeMap which will contain the fractional solution x to the first LP relaxation
//6 The value of the approximated solution
//7 The value of the first LP relaxation

#endif
//void solve_lp(lemon::ListGraph *,lemon::ListGraph::EdgeMap<double> *,lemon::ListGraph::EdgeMap<int> *, RequirementFunction*, lemon::ListGraph::EdgeMap<int> *, lemon::ListGraph::Edge *, double*, bool );    


