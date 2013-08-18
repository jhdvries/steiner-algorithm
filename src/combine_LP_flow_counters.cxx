#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/glpk.h>
#include <lemon/lp.h>
#include "SourceTargetArc.h"

int main(){
    
  //define graph
  lemon::ListGraph g;

  //cost function on the edges
  lemon::ListGraph::EdgeMap<int> c(g);
 
  //Adding 4 nodes to the graph
  for(int i=0; i<4; i++){
    g.addNode();
  }

  //create edges to make graph complete and assigning cost to edges
  for (lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID ;++u){
    for (lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID ;++v){
      if(u!=v){
        
        //initialise edge (uv)
        lemon::ListGraph::Edge temp_edge= g.addEdge(u,v);
                                         
        //assigns cost function
       // if(g.id(u)>g.id(v)) c[temp_edge]=g.id(u)-g.id(v);
       // else c[temp_edge]=g.id(v)-g.id(u);
        c[temp_edge] =1;

        std::cout << "Added edge with ids u: " << g.id(u) << " v: " <<  g.id(v) << " and costs " << c[temp_edge] <<  std::endl;
      }
      else{
        std::cout << "Didn't make node, because the Nodes were the same" << std::endl; 
      }
    }
  }

  //add requirement function defined over two nodes


  //define LP
  lemon::Lp lp;

   std::cout<< "Defined LP p " << std::endl; 

  //define capacity variable x and flow variable f
  lemon::ListGraph::EdgeMap<lemon::Lp::Col> x(g);
  std::map<SourceTargetArc, lemon::Lp::Col> f;

   std::cout<< "Defined LP and initialised both the x variable map and the f variable map " << std::endl;; 

    lp.addColSet(x);
  //Assign capacity constraints to x and f and initialising f variables
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    
    //capacity constraint for x
    lp.colLowerBound(x[e],0);
    lp.colUpperBound(x[e],1);
  }
 
 //assign upper bounds to flow variables
 for(lemon::ListGraph::ArcIt a(g); a != lemon::INVALID; ++a){ 
    //loop over all pairs of nodes
    for(lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID; ++u){
      for(lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID; ++v){
        if(u!=v){
          //initialisng f variables for eacht SourceTargetArc
          SourceTargetArc f1(u,v,a);
          f[f1]=lp.addCol();

          //capacity constraints for f
          lp.colLowerBound(f[f1],0);

          //upper bound for flow
          lp.addRow(x[lemon::ListGraph::Edge(a)]-f[f1]>=0);

          if( g.direction(a)== true)std::cout<< "arc " << g.id(g.u(a)) << " " << g.id(g.v(a)) << " with arc id " << g.id(a) << " has the same direction as edge: " << g.id(g.u(lemon::ListGraph::Edge(a)))<< " " << g.id(g.v(lemon::ListGraph::Edge(a))) << "]"  <<  std::endl;       
          else std::cout<< "arc " << g.id(g.u(a)) << " " << g.id(g.v(a)) << " with arc id " << g.id(a) << " has the same direction as edge: " << g.id(g.u(lemon    ::ListGraph::Edge(a)))<< " " << g.id(g.v(lemon::ListGraph::Edge(a))) << "]"  <<  std::endl; 
       }
      }
    }   
  }
  
  //Create flow constraints as follows
  //We set up the conservation of flow for non source, target node n
  //And the flow value constraint for the source n
  //this is done for all pair (of source and target) u,v
  
  for(lemon::ListGraph::NodeIt source(g); source!=lemon::INVALID; ++source){
    for(lemon::ListGraph::NodeIt target(source); target!=lemon::INVALID; ++target){
      if (source!=target){ 
        //define flowval, bij ouflow minus inflow of source
        lemon::Lp::Expr flowVal;
        for (lemon::ListGraph::OutArcIt arc(g,source); arc != lemon::INVALID; ++arc){
          SourceTargetArc f1(source,target,arc);
          flowVal += f[f1];
        }
        for (lemon::ListGraph::InArcIt arc(g,source); arc != lemon::INVALID; ++arc){ 
          SourceTargetArc f1(source,target,arc); 
          flowVal -= f[f1];
        }
        //set connectivity requirement to 2 fro the time being
        lp.addRow(flowVal>=1);
        
        //formulate conservation of flow constraints for the all non-source and non-target nodes
        for(lemon::ListGraph::NodeIt n(g); n!=lemon::INVALID; ++n){
          if(n!=source && n!= target){
            lemon::Lp::Expr nodeFlow;
            for (lemon::ListGraph::OutArcIt arc(g,n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(source,target,arc); 
              nodeFlow -= f[f1];
            }
            for (lemon::ListGraph::InArcIt arc(g,n); arc != lemon::INVALID; ++arc){
              SourceTargetArc f1(source,target,arc); 
              nodeFlow -= f[f1];
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
  for(lemon::ListGraph::EdgeIt e(g); e!=lemon::INVALID; ++e) obj+=c[e]*x[e];
  
  //minimization problem 
  lp.min();
  lp.obj(obj);
  lp.solve();
  
  //print results
  if (lp.primalType() == lemon::Lp::OPTIMAL) {
    
    //objective function value
    std::cout << "Objective function value: " << lp.primal() << std::endl;
    
    //print all edges and the corresponding x values
    for(lemon::ListGraph::EdgeIt e(g); e!=lemon::INVALID; ++e){
      std::cout << "x[" << g.id(g.u(e)) << g.id(g.v(e)) << "] = "<< lp.primal(x[e])  << std::endl;
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
