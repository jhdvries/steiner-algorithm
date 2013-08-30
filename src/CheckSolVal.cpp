#include "CheckSolVal.h"


//Solution check, going through all solutions 
//checking whether there is a solution within the upper and lower bound,
//and if last input bool is true it checks wheter the input is integer
bool check_sol_val(lemon::ListGraph *g, lemon::ListGraph::EdgeMap<double> *y, lemon::ListGraph::EdgeMap<int> *F, double lowerbound, double upperbound, bool integercheck ){
 
 //if the boolean is 1, we are checking whether the solution contains a non-integral variable. If this is true then a true is returned.
  if(integercheck == 1){  
    for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
      if((*F)[e]==0){
        if((*y)[e] > 1e-6){//error margin of the solver
          if((*y)[e] < 1) return 1;
        }
      }
    }   
  }
 
  // if the boolean is false then we look for the factional values between the lower and the upper bound and return true if one is found.
  else{
    for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
      if((*F)[e]==0){ 
        if((*y)[e] >= lowerbound){
          if((*y)[e] <= upperbound) return 1;
        }
      }
    }
  }
  return 0;
}
