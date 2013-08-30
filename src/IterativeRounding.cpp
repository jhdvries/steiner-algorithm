#include "IterativeRounding.h"

//Largest function it executes the while loop in the algorithm and iteratively rounds solutions until an optimal solution is found
void iterative_rounding(lemon::ListGraph *g, lemon::ListGraph::EdgeMap<double> *c, RequirementFunction *r, lemon::ListGraph::EdgeMap<double> *sol , lemon::ListGraph::EdgeMap<double> *rsol , double *valsol , double *valrsol ){

  
  //initialise result map
  lemon::ListGraph::EdgeMap<double> y((*g));
  
  //initalise Steiner Edge Set, initial value 0
  lemon::ListGraph::EdgeMap<int> F((*g));
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e) (F)[e] = 0;

  //used to store value of oringal lp relaxation solution
  double valorigallp;

  //used to store value of lp relaxation for comparison purposes in while loop
  double valiteratelp;
  
  //First solve LP relaxation of orignal problem
  lemon::ListGraph::EdgeIt i((*g));
  solve_lp(&(*g), &y, &*c, &*r, &F, &i, &valorigallp, 0);   
 
  //Store solution to LP-relaxation of the IP
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e)  (*rsol)[e]=y[e];

  //store solution 
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e)  (*rsol)[e]=y[e];
  
  valiteratelp=valorigallp;

  //Start  while loop so while there are non integral solutions in x
  //The check of this statement is a function by itself
  while(check_sol_val(&(*g),&y,&F, 0, 1,1)){

    // if there are fractional values higher then a half
    if(check_sol_val(&(*g),&y,&F, 0.5, 1,0)){
      
      //include all edges uv  with x(uv) >= 1/2 in Steiner Network
      for(lemon::ListGraph::EdgeIt e((*g)); e != lemon::INVALID; ++e){
        if(y[e]>=0.5 && F[e]!= 1){
          F[e]=1;       
      
       // can be used to show which edge has been included
       // std::cout<<"inlduded edge "<< (*g).id((*g).u(e))<<" " <<(*g).id((*g).v(e)) <<std::endl;}
       }
     }
    }
    else{ 
    
      //as non of the (residual) LP solution variables have value >=1/2
      //We iteratively check which one can be assigned a higher value 
      //Without raising the total cost of the solution
      for(lemon::ListGraph::EdgeIt e((*g)); e != lemon::INVALID; ++e){
        
        //double to store solution value with added constraint
        double valconstrlp;
        
        //if statement to prevent already included edges to be considered
        if(F[e]==0){
          solve_lp(&(*g), &y, &*c, &*r, &F, &e, &valconstrlp, 1);          

          //can be used to print inbetween results 
          //std::cout<< "constraining edge e" << (*g).id(e) << "and total cost is"<< valconstrlp  << std::endl;

          // for(lemon::ListGraph::EdgeIt k(*g); k !=lemon::INVALID; ++k)
          //   std::cout << "x[ " << (*g).id((*g).u(k))<<" " <<(*g).id((*g).v(k)) << "] = "  << y[k] << std::endl;

          //if true then we can include edge uv in the steiner network  and break from for the loop 
          if(valconstrlp<=valiteratelp+1e-6){//error margin of the solver
          
            // can be used to show which edge has been included
            // std::cout<<"inlduded edge "<< (*g).id((*g).u(e))<<" " <<(*g).id((*g).v(e)) <<std::endl;}
     
            F[e]=1;
            break;
          }
        }
      }
    }
      
    //Solve LP again for the next loop 
    lemon::ListGraph::EdgeIt e((*g));
    solve_lp(&(*g), &y, &*c, &*r, &F, &e, &valiteratelp, 0);
 
  // can be used to print inbetween results
  //  std::cout<< "At the end of the loop and total cost is"<< valiteratelp  << std::endl;
  // 
  //  for(lemon::ListGraph::EdgeIt k(*g); k !=lemon::INVALID; ++k)
  //    std::cout << "x[ " << (*g).id((*g).u(k))<<" " <<(*g).id((*g).v(k)) << "] = "  << y[k] << std::endl;
    
  }


  //assign values as they will be returned to the main program 
  (*valrsol)= valorigallp;
  (*valsol)= valiteratelp;

  //Store integral final solution
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e)  (*sol)[e]=y[e];

}



