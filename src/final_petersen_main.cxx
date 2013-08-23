#include <iostream>
#include <lemon/list_graph.h>
#include "GenerateGraph.h"
#include "AssignEdgeCost.h"
#include "AssignConnectivityRequirement.h"
#include "RequirementFunction.h"
#include "CreateSolveLp.h"
#include "CheckSolVal.h"
#include "IterativeRounding.h"


int main(){
  
  //Generate a graph with nodes and edges
  lemon::ListGraph g;
  generate_peterson_graph(&g,8);

  //assigns a cost function to the edges fills it with a maximum double
  lemon::ListGraph::EdgeMap<double> c(g);
  fill_cost_constant(&c, &g, 1);

  
  //Assigns the requirements to all node pairs
  RequirementFunction r;
  assign_connectivity_constant(&r,&g,1);
  
  //retrieves value of final solution
  double valsol;

  //retrieves value of LP relaxation solution
  double valrsol;

  //Final solution variable values
  lemon::ListGraph::EdgeMap<double> sol(g);

  //Relaxation  solution variable values
  lemon::ListGraph::EdgeMap<double> rsol(g);
  
  //iterative rounding while loop as describe in Algorithm 4
  iterative_rounding(&g, &c, &r, &sol , &rsol , &valsol , &valrsol );
  
  //Present results approximation algorithm
  std::cout << "The solution of the LP relaxation has cost" << valrsol  << std::endl;
  
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    std::cout << "x(LP-relax)[" << g.id(g.u(e))<<" " <<g.id(g.v(e)) << "] = "  << rsol[e] <<  std::endl;
  }
 
  //Present results approximation algorithm
  std::cout << "The solution found by the approximation algorithm has cost" << valsol  << std::endl;
  
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    std::cout << "x[ " << g.id(g.u(e))<<" " <<g.id(g.v(e)) << "] = "  << sol[e] << std::endl;
  }

 
  return 0;
}



