#include <CreateSolveLp.h> 
void solve_lp(lemon::ListGraph *g, lemon::ListGraph::EdgeMap<double> *y, lemon::ListGraph::EdgeMap<int> *c, RequirementFunction *r, lemon::ListGraph::Edge *changeedge, bool change){

  //define LP
  lemon::Lp lp;

  std::cout<< "Defined LP p " << std::endl; 

  //define capacity variable x and flow variable f
  lemon::ListGraph::EdgeMap<lemon::Lp::Col> x((*g));
  std::map<int, lemon::Lp::Col> f;

  std::cout<< "Defined LP and initialised both the x variable map and the f variable map " << std::endl;; 

  lp.addColSet(x);
  //Assign capacity constraints to x and f and initialising f variables
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
   
   //if we need to fix variable on value >= 1/2
   if(change == 1  && e == (*changeedge)){
      lp.colLowerBound(x[e],0);
      lp.colUpperBound(x[e],1);
    }
    else{
      //capacity constraint for x
      lp.colLowerBound(x[e],0);
      lp.colUpperBound(x[e],1);
    }
  }


 //assign upper bounds to flow variables
 for(lemon::ListGraph::ArcIt a((*g)); a != lemon::INVALID; ++a){ 
    
    //loop over all pairs of nodes
    for(lemon::ListGraph::NodeIt source((*g)); source!=lemon::INVALID; ++source){
      for(lemon::ListGraph::NodeIt target(source); target!=lemon::INVALID; ++target){
        if(source!=target){
          std::cout << "Ard id: " <<(*g).id(a) << std::endl;
          std::cout << "  Source ID: " << (*g).id(source) << " Target ID: " << (*g).id(target) << std::endl;
          std::cout << "  arc direction aligned with edge: " << (*g).direction(a) << std::endl;
          std::cout << "  Size of flow variables f: " << f.size() << std::endl; 
          
          //initialisng f variables for eacht SourceTargetArc
          SourceTargetArc f1(&(*g),source,target,a);
          
          // f.insert(std::pair<SourceTargetArc, lemon::Lp::Col> (f1,lp.addCol()));
          std::map<SourceTargetArc,lemon::Lp::Col>::iterator it;
  
          f[f1.id()]=lp.addCol();
          std::cout << "  Size of flow variables f: " << f.size() << std::endl; 
          if (f.find(f1.id())!=f.end()) std::cout <<"  yep"<<std::endl;
          else  std::cout << "  I CANNOT FIND THE ELEMENT THE I JUST ADDED" << std::endl;

          //capacity constraints for f
          lp.colLowerBound(f[f1.id()],0);
          lp.colUpperBound(f[f1.id()],1);  
          
          //upper bound for flow
          lp.addRow(x[lemon::ListGraph::Edge(a)]-f[f1.id()]>=0);
       }
      }
    }   
  }
 
 //Create flow constraints as follows
  //We set up the conservation of flow for non source, target node n
  //And the flow value constraint for the source n
  //this is done for all pair (of source and target) u,v
  
  for(lemon::ListGraph::NodeIt source((*g)); source!=lemon::INVALID; ++source){
    for(lemon::ListGraph::NodeIt target(source); target!=lemon::INVALID; ++target){
      if (source!=target){ 
        //define flowval, bij ouflow minus inflow of source
        std::cout << "Source id: " << (*g).id(source) << "Target id: " << (*g).id(target) << std::endl;
        lemon::Lp::Expr flowVal;
        for (lemon::ListGraph::OutArcIt arc((*g),source); arc != lemon::INVALID; ++arc){
          SourceTargetArc f1(&(*g),source,target,arc);
          flowVal += f[f1.id()];
          std::cout << "    Outarc  ID: " << (*g).id(arc) << std::endl;
        }
        for (lemon::ListGraph::InArcIt arc((*g),source); arc != lemon::INVALID; ++arc){ 
          SourceTargetArc f1(&(*g),source,target,arc); 
          flowVal -= f[f1.id()];
          std::cout << "    Intarc  ID: " << (*g).id(arc) <<std::endl;
        }
        //set connectivity requirement to 2 fro the time being
        lp.addRow(flowVal>=(*r).getValue(source, target));
        
        //formulate conservation of flow constraints for the all non-source and non-target nodes
        for(lemon::ListGraph::NodeIt n((*g)); n!=lemon::INVALID; ++n){
          if(n!=source && n!= target){
            lemon::Lp::Expr nodeFlow;
            for (lemon::ListGraph::OutArcIt arc((*g),n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(&(*g),source,target,arc); 
              nodeFlow += f[f1.id()];
            }
            for (lemon::ListGraph::InArcIt arc((*g),n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(&(*g),source,target,arc); 
              nodeFlow -= f[f1.id()];
            }
     
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
  
  //print results
  if (lp.primalType() == lemon::Lp::OPTIMAL) {
    
    //objective function value
    std::cout << "Objective function value: " << lp.primal() << std::endl;
    
    //print all edges and the corresponding x values
    for(lemon::ListGraph::EdgeIt e((*g)); e!=lemon::INVALID; ++e){
      (*y)[e] = lp.primal(x[e]); 
      std::cout << "x[" << (*g).id((*g).u(e)) << (*g).id((*g).v(e)) << "] = "<< lp.primal(x[e])  << std::endl;
    }
  }

  //When it doesn't
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
