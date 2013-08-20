#include "AssignConnectivityRequirement.h"

void assign_connectivity_random(RequirementFunction *r, lemon::ListGraph *g){
  for(lemon::ListGraph::NodeIt u((*g)); u !=lemon::INVALID; ++u){ 
    for(lemon::ListGraph::NodeIt v((*g)); v !=lemon::INVALID; ++v)(*r).assignValue(u,v,rand() % 3 + 1);
  }
}

//All cost are of the integer value u
void assign_connectivity_constant(RequirementFunction *r, lemon::ListGraph *g, int k){
  for(lemon::ListGraph::NodeIt u((*g)); u !=lemon::INVALID;++u){
    for(lemon::ListGraph::NodeIt v((*g)); v !=lemon::INVALID;++v)(*r).assignValue(u,v,k);
  }
}

