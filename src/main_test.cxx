#include <iostream>
#include <lemon/list_graph.h>
#include "GenerateGraph.h"
#include "AssignEdgeCost.h"
#include "AssignConnectivityRequirement.h"
#include "RequirementFunction.h"
#include "CreateSolveLp.h"
#include "CheckSolVal.h"


int main(){
  
  //Generate a graph with nodes and edges
  lemon::ListGraph g;
  generate_complete_graph(&g,10);
//  generate_peterson_graph(&g);

  //assigns a cost function to the edges
  lemon::ListGraph::EdgeMap<int> c(g);
  fill_cost_random(&c, &g);

  //Test the costs
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
  std::cout << "The cost Edge is " << c[e] << std::endl;}
  
  //Assigns the requirements to all node pairs
  RequirementFunction r;
  assign_connectivity_random(&r,&g);

  //Checks the requirements
  for(lemon::ListGraph::NodeIt u(g); u !=lemon::INVALID; ++u){
    for(lemon::ListGraph::NodeIt v(g); v !=lemon::INVALID; ++v){
      std::cout << "Requirement between " << g.id(u) <<" and" << g.id(v) << " is " <<r.getValue(u,v) << std::endl;
    }
  }
  
  //Weird function for finding some edge for input in the solver
  lemon::ListGraph::EdgeMap<double> y(g);
  int i;
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    i++;
    if(i==2)solve_lp(&g, &y, &c, &r, &e, 1);   
  }
  
  //Prints  output y
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    std::cout<< "the solution val is " << y[e] <<std::endl;
  }
  
  //Output checker
  if(check_sol_val(&g,&y, 0, 1,1)){
    std::cout<< "There is a non- integral value in the solution"<< std::endl;  
    if(check_sol_val(&g,&y, 0.5, 1,0)){
      std::cout<< "There is a variable with fractional value >= then 1/2 in the solution"<< std::endl;
    }
  }
  else std::cout<< "All solution values are integral"<< std::endl;
  


  return 0;
}

//void solve_lp(lemon::ListGraph *,lemon::ListGraph::EdgeMap<double> *,lemon::ListGraph::EdgeMap<int> *, RequirementFunction*, lemon::ListGraph::Edge, bool );    



