#include <CreateSolveLP.h> 

//Creates the compact LP for the IP or the residual IP depending on the iteration of the algorithm
void solve_lp(lemon::ListGraph *g, lemon::ListGraph::EdgeMap<double> *y, lemon::ListGraph::EdgeMap<double> *c, RequirementFunction *r, lemon::ListGraph::EdgeMap<int> *F, lemon::ListGraph::Edge *changeedge, double *val , bool change){

  //define LP
  lemon::Lp lp;

  //define capacity variable x and flow variable f
  lemon::ListGraph::EdgeMap<lemon::Lp::Col> x((*g));
  lp.addColSet(x);
  std::map<int, lemon::Lp::Col> f;
  
  //Assign capacity constraints to x and f and initialising f variables
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
   
    //if we need to fix variable on value >= 1/2 extra constraint
    //This is only required if boolean changeedge is true
    //In iterative rounding this happens only if there is a solution 
    //Where all values are fractiona and < 1/2
    if(change == 1  && e == (*changeedge)){
      lp.colLowerBound(x[e],0.5);
      lp.colUpperBound(x[e],1);
    }
    else{
      if((*F)[e]==1){     
        
        //these variables need to be fixed at value 1 as they are in the Steiner network already
        //In such a case we are now solving the residual problem so we need a partial solution
        lp.colLowerBound(x[e],1);
        lp.colUpperBound(x[e],1);
      }
      else{
        
        //all remaining cases, that is the case when the have not been fixed by either constraint
        //or previouw inclusion in Steiner network
        lp.colLowerBound(x[e],0);
        lp.colUpperBound(x[e],1);
      }   
    }
  }


  //assign upper bounds to flow variables
  //to do this we will need to loop over all arcs 
  for(lemon::ListGraph::ArcIt a((*g)); a != lemon::INVALID; ++a){ 
    
    //and also loop over all pairs of nodes
    for(lemon::ListGraph::NodeIt source((*g)); source!=lemon::INVALID; ++source){
      for(lemon::ListGraph::NodeIt target(source); target!=lemon::INVALID; ++target){
        if(source!=target){
          
          //using template to construct the right index for the flow variables
          SourceTargetArc f1(&(*g),source,target,a);
          
          //now adding the flow variable to the lp
          f[f1.id()]=lp.addCol();

          //capacity constraints for the flow variable, without looking at the upperbound set by x
          lp.colLowerBound(f[f1.id()],0);
          lp.colUpperBound(f[f1.id()],1);  
          
          //upper bound for flow by variable x
          lp.addRow(x[lemon::ListGraph::Edge(a)]-f[f1.id()]>=0);
       }
      }
    }   
  }
 
  //Create flow constraints as follows
  //Define flow value constraint for the source 
  //Define the conservation of flow for non source, target nodes 
  //this is done for all pair (of source and target) u,v
  
  for(lemon::ListGraph::NodeIt source((*g)); source!=lemon::INVALID; ++source){
    for(lemon::ListGraph::NodeIt target(source); target!=lemon::INVALID; ++target){
      if (source!=target){ 
        
        //linear expression used to formulate the value of 
        //the flow between the source and the target 
        lemon::Lp::Expr flowVal;
        
        //all outflow is added
        for (lemon::ListGraph::OutArcIt arc((*g),source); arc != lemon::INVALID; ++arc){
          SourceTargetArc f1(&(*g),source,target,arc);
          flowVal += f[f1.id()];
        }

        //all inflow substracted
        for (lemon::ListGraph::InArcIt arc((*g),source); arc != lemon::INVALID; ++arc){ 
          SourceTargetArc f1(&(*g),source,target,arc); 
          flowVal -= f[f1.id()];
        }
        
        //for every pair if the following holds, 
        //by teh minflow maxcut theorem
        //there are at least r(ij) edge disjoint paths between i and j
        lp.addRow(flowVal>=(*r).getValue(source, target));
        
        //formulate conservation of flow constraints for the all non-source and non-target nodes
        for(lemon::ListGraph::NodeIt n((*g)); n!=lemon::INVALID; ++n){
          if(n!=source && n!= target){
           
            //now the conservation of flow is defined for every node
            lemon::Lp::Expr nodeFlow;

            //adding outflow
            for (lemon::ListGraph::OutArcIt arc((*g),n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(&(*g),source,target,arc); 
              nodeFlow += f[f1.id()];
            }

            //subtracting inflow
            for (lemon::ListGraph::InArcIt arc((*g),n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(&(*g),source,target,arc); 
              nodeFlow -= f[f1.id()];
            }
            
            // and the constraint is added to the LP
            lp.addRow(nodeFlow==0);
          }
        }
      }
    }
  }
  
  //defining the objective function 
  lemon::Lp::Expr obj;

  //cost of all arcs included is the objective functions
  for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e) obj+=(*c)[e]*x[e];
  
  //minimization problem 
  lp.min();
  lp.obj(obj);
  lp.solve();
  
  //returns value if we have an optimal solution. And  if the problem was not optimally solved why.
  if (lp.primalType() == lemon::Lp::OPTIMAL) {
    
    //objective function value
    (*val)=lp.primal();

    //returning solution value for edge  variables
    for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e){
      (*y)[e] = lp.primal(x[e]); 
    }
  }

  //Returning reason for no optimal solution
  else {
    std::cout << "Optimal solution not found." << std::endl;

    if(lp.primalType() == lemon::Lp::UNDEFINED){
      std::cout << "Because the problem is undefined" << std::endl;
    }
    if(lp.primalType() == lemon::Lp::INFEASIBLE){
      std::cout << "Because the problem is infeasible" << std::endl;
    }
    if(lp.primalType() == lemon::Lp::FEASIBLE){
      std::cout << "Althoug the problem is feasible" << std::endl;
    }
    if(lp.primalType() == lemon::Lp::UNBOUNDED){
      std::cout << "Because the problem is unbounded" << std::endl;
    }
  }
}
