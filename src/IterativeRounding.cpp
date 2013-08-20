#include "IterativeRounding.h"

void iterative_rounding(lemon::ListGraph *g, lemon::ListGraph::EdgeMap<int> *c, RequirementFunction *r, lemon::ListGraph::EdgeMap<double> *sol , lemon::ListGraph::EdgeMap<double> *rsol , double *valsol , double *valrsol ){

  
  //initialise result map
  lemon::ListGraph::EdgeMap<double> y((*g));
  
  //initalise Steiner Edge Set, initial value 0
  lemon::ListGraph::EdgeMap<int> F((*g));
  fill_cost_constant(&F, &(*g), 0);
  
  //used to store value of oringal lp relaxation solution
  double valorigallp;

  //used to store value of lp relaxation for comparison purposes in while loop
  double valiteratelp;
  
  //First solve LP relaxation of orignal problem
  lemon::ListGraph::EdgeIt i((*g));
  solve_lp(&(*g), &y, &*c, &*r, &F, &i, &valorigallp, 0);   
  
  //store solution 
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e)  (*rsol)[e]=y[e];
  
  valiteratelp=valorigallp;

  //start imortatnt while loop so while there are non integral solutions in x
  while(check_sol_val(&(*g),&y,&F, 0, 1,1)){
    
    // if there are fractional values higher then a half
    if(check_sol_val(&(*g),&y,&F, 0.5, 1,0)){
      
      //include the edges in the steiner graph
      for(lemon::ListGraph::EdgeIt e((*g)); e != lemon::INVALID; ++e){
        if(y[e]>=0.5 ) F[e]=1;       
      }
    }
    else{ 
    //for all edges calculate the value of the lp with added restriction taht x[e]>= 1/2 and compare
      for(lemon::ListGraph::EdgeIt e((*g)); e != lemon::INVALID; ++e){
        double valconstrlp;
        solve_lp(&(*g), &y, &*c, &*r, &F, &e, &valconstrlp, 1);
       
        //if true then we can fix x[e] as well and break from the loop 
        if(valconstrlp<=valiteratelp){
          F[e]=1;
          break;
        }
      }
    }
    lemon::ListGraph::EdgeIt e((*g));
    solve_lp(&(*g), &y, &*c, &*r, &F, &e, &valiteratelp, 0);
  }

  //Prints  output y
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
    std::cout<< "the solution val is " << y[e] <<std::endl;
  }
  
  //Output checker
  if(check_sol_val(&(*g),&y,&F, 0, 1,1)){
    std::cout<< "There is a non- integral value in the solution"<< std::endl;  
    if(check_sol_val(&(*g),&y,&F, 0.5, 1,0)){
      std::cout<< "There is a variable with fractional value >= then 1/2 in the solution"<< std::endl;
    }
  }
  else std::cout<< "All solution values are integral"<< std::endl;
  
  //assign values as they will be returned to the main program 
  (*valrsol)= valorigallp;
  (*valsol)= valiteratelp;

  //Store fractional solution
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e)  (*sol)[e]=y[e];

}



