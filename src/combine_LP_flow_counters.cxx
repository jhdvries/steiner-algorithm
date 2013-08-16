#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/glpk.h>
#include <lemon/lp.h>
#include "SourceTargetEdge.h"

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
        if(g.id(u)>g.id(v)) c[temp_edge]=g.id(u)-g.id(v);
        else c[temp_edge]=g.id(v)-g.id(u);

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
  
  //define capacity variable x and flow variable f
  lemon::ListGraph::EdgeMap<lemon::Lp::Col> x(g);
  std::map<SourceTargetEdge, lemon::Lp::Col> f;

  //Assign capacity constraints to x and f and initialising f variables
  for(lemon::ListGraph::EdgeIt e(g); e !=lemon::INVALID; ++e){
    
    //capacity constraint for x
    lp.colLowerBound(x[e],0);
    lp.colUpperBound(x[e],1);

    //loop over all pairs of nodes
    for(lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID; ++u){
      for(lemon::ListGraph::NodeIt v(g); v!=lemon::INVALID; ++v){
       
        //initialisng f variables for eacht SourceTargetEdge
        SourceTargetEdge f1(u,v,e);
        f[f1]=lp.addCol();

        //capacity constraints for f
        lp.colLowerBound(f[f1],0);
        lp.colUpperBound(f[f1],1);

        std::cout<< "upper Lowerbounds for x-var and flow-var on edge " << g.id(u) << g.id(v) << " defined" << std::cout; 
      }
    }   
  }
  
  //Create flow constraints as follows
  //We set up the conservation of flow for non source, target node n
  //And the flow value constraint for the source n
  //this is done for all pair (of source and target) u,v
  
  for(lemon::ListGraph::NodeIt n(g); n!=lemon::INVALID; ++n){
    for(lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID; ++u){
      lemon::ListGraph::NodeIt w(g,u);
      ++w;
      for(lemon::ListGraph::NodeIt v(g,w); v!=lemon::INVALID; ++v){
        
        //if n is the source, define the value of the flow
        if(n==u){
         
          //Expr y is value of flow we loop over outarcs of n to create value of flow
          lemon::Lp::Expr y;
          
          //First iterating over inflow
          for(lemon::ListGraph::OutArcIt a(g,n); a!= lemon::INVALID; ++a){ 
            
            //initialising SourceTargetEdge template and adding to arc flow to expr
            SourceTargetEdge f1(u,v,a);            
            y+=f[f1];
          }

          //Second iterating over outflow
          for(lemon::ListGraph::InArcIt a(g,n); a!= lemon::INVALID; ++a){ 

            //initialising SourceTargetEdge template and adding to arc flow to expr
            SourceTargetEdge f1(u,v,a);            
            y+=f[f1];
          }

          //The value of the flow is equal to the number of internally vertex/edge? disjoint paths
          lp.addRow(y >= g.id(v)-g.id(u));
        }
        else{
          if(n!=v){
          
            //Expr y is value of flow we loop over outarcs of n to create value of flow
            lemon::Lp::Expr y;
          
            //First iterating over inflow
            for(lemon::ListGraph::OutArcIt a(g,n); a!= lemon::INVALID; ++a){ 
            
              //initialising SourceTargetEdge template and adding to arc flow to expr
              SourceTargetEdge f1(u,v,a);            
              y+=f[f1];
            }

            //Second iterating over outflow
            for(lemon::ListGraph::InArcIt a(g,n); a!= lemon::INVALID; ++a){ 

              //initialising SourceTargetEdge template and adding to arc flow to expr
              SourceTargetEdge f1(u,v,a);            
              y+=f[f1];
            }

            //The value of the flow is equal to the number of internally vertex/edge? disjoint paths
            lp.addRow(y = 0);
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
    //  std::cout << "x[" << g.id(g.u(e)) << g.id(g.v(e)) << "] = " << x[e] << std::endl;
    }
  }

  //When it doesn't
  else {
    std::cout << "Optimal solution not found." << std::endl;
  }



}
