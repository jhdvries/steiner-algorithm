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
  
//  for(int s =5 ; s<=14 ; s++){
    //Generate a graph with nodes and edges
    lemon::ListGraph g;
    generate_complete_graph(&g,13);//s);
  
    for(lemon::ListGraph::EdgeIt e(g); e!=lemon::INVALID; ++e)
      std::cout<< "edge from node " << g.id(g.u(e)) << " to node " << g.id(g.v(e)) << std::endl;
    
    //assigns a cost function to the edges fills it with a maximum double
    lemon::ListGraph::EdgeMap<double> c(g);
    fill_cost_random(&c, &g, 3);
  
    //Test the costs
    for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    std::cout << "The cost Edge is " << c[e] << std::endl;}
    
    //Assigns the requirements to all node pairs
    RequirementFunction r;
    assign_connectivity_random(&r,&g,2);
    
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
    
//    //Present results approximation algorithm
//   std::cout << "The solution found by the approximation algorithm has cost" << valsol  << std::endl;
// 
//   for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
//     std::cout << "x[ " << g.id(g.u(e))<<" " <<g.id(g.v(e)) << "] = "  << sol[e] << std::endl;
//   }
//
//   //Present results approximation algorithm
//   std::cout << "The solution of the LP relaxation has cost" << valrsol  << std::endl;
//   std::cout << "The solution found by the approximation algorithm has cost" << valsol  << std::endl;
//
//   for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
//     std::cout << "x(LP-relax)[" << g.id(g.u(e))<<" " <<g.id(g.v(e)) << "] = "  << rsol[e] << " this edge has costs " << c[e] << std::endl;
//   }
   std::cout << "The solution of the LP relaxation has cost" << valrsol  << std::endl;
   std::cout << "The solution found by the approximation algorithm has cost" << valsol  << std::endl;
//   boolean aprox= valsol/valrsol;
//   std::cout << "the integralit Gap is" << aprox  << std::endl;
//  }  

return 0;
}


