#include "AssignConnectivityRequirement.h"

//Assign connectivity requirement randomly input where i is the maximum requirement 
void assign_connectivity_random(RequirementFunction *r, lemon::ListGraph *g, int i){
 
  //to avoid the same requirement assignment in each graph we chose to seed on the time
  srand(time(0));
  for(lemon::ListGraph::NodeIt u((*g)); u !=lemon::INVALID; ++u){ 
    for(lemon::ListGraph::NodeIt v((*g)); v !=lemon::INVALID; ++v)(*r).assignValue(u,v,rand() % i + 1);
  }
}

//Assign the same integer connectivity  requirement  i to each pair
void assign_connectivity_constant(RequirementFunction *r, lemon::ListGraph *g, int k){
  for(lemon::ListGraph::NodeIt u((*g)); u !=lemon::INVALID;++u){
    for(lemon::ListGraph::NodeIt v((*g)); v !=lemon::INVALID;++v)(*r).assignValue(u,v,k);
  }
}

