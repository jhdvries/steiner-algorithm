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
  

  //Solve LP before while loop
  //Weird function for finding some edge for input in the solver
  
  //initialise result map
  lemon::ListGraph::EdgeMap<double> y(g);
  
  //initalise Steiner Edge Set, initial value 0
  lemon::ListGraph::EdgeMap<int> F(g);
  fill_cost_constant(&F, &g, 0);
  
 
  //Solve LP before while loop
  //Weird function for finding some edge for input in the solver
  int i;
  
  //used to store value of oringal lp relaxation solution
  double valorigallp;

  //used to store value of lp relaxation for comparison purposes in while loop
  double valiteratelp;

  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    i++;
    if(i==2) solve_lp(&g, &y, &c, &r, &F, &e, &valorigallp, 0);   
  }
  
  valiteratelp=valorigallp;

  //start imortatnt while loop so while there are non integral solutions in x
  while(check_sol_val(&g,&y,&F, 0, 1,1)){
    
    // if there are fractional values higher then a half
    if(check_sol_val(&g,&y,&F, 0.5, 1,0)){
      
      //include the edges in the steiner graph
      for(lemon::ListGraph::EdgeIt e(g); e != lemon::INVALID; ++e){
        if(y[e]>=0.5 ) F[e]=1;       
      }
    }
    else{ 
    //for all edges calculate the value of the lp with added restriction taht x[e]>= 1/2 and compare
      for(lemon::ListGraph::EdgeIt e(g); e != lemon::INVALID; ++e){
        double valconstrlp;
        solve_lp(&g, &y, &c, &r, &F, &e, &valconstrlp, 1);
       
        //if true then we can fix x[e] as well and break from the loop 
        if(valconstrlp<=valiteratelp){
          F[e]=1;
          break;
        }
      }
    }
    lemon::ListGraph::EdgeIt e(g);
    solve_lp(&g, &y, &c, &r, &F, &e, &valiteratelp, 0);
  }

  //Prints  output y
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    std::cout<< "the solution val is " << y[e] <<std::endl;
  }
  
  //Output checker
  if(check_sol_val(&g,&y,&F, 0, 1,1)){
    std::cout<< "There is a non- integral value in the solution"<< std::endl;  
    if(check_sol_val(&g,&y,&F, 0.5, 1,0)){
      std::cout<< "There is a variable with fractional value >= then 1/2 in the solution"<< std::endl;
    }
  }
  else std::cout<< "All solution values are integral"<< std::endl;
  


  return 0;
}


