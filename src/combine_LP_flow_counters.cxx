#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/glpk.h>
#include <lemon/lp.h>
#include "SourceTargetEdge.h"

int main(){
    
  //define graph
  lemon::ListGraph g;

  //cost function on the edges
  lemon::ListGraph::EdgeMap<edge> c(g);
 
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

        std::cout << "Added edge with ids u: " << g.id(u) << " v: " <<  g.id(v) << "and costs" << c[temp_edge] <<  std::endl;
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
  lemon::ListGraph::EdgeMap <LP::col> x(g);
  std::map<SourceTargetEdge, lemon::Lp::Col> f;

  //Assign capacity constraints to x and f
  for(lemon::ListGraph::EdgeIt e(g); e != Invalid; ++e){
    
    //capacity constraint for x
    lp.colLowerBound(x[e],0);
    lp.colUpperBound(x[e],1);

    //loop over all pairs of nodes
    for(lemon::ListGraph::NodeIt u(g); u!=Invalid; ++u){
      for(lemon::ListGraph::NodeIt u(g); u!=Invalid; ++u){
       
        //capacity constraints for f
        lp.colLowerBound(f[u][v][e],0);
        lp.colupperBound(f[u][v][e],x[e]);
       
      }
    
    }   
  }
  
  //Create flow constraints as follows
  //We set up the conservation of flow for non source, target node n
  //And the flow value constraint for the source n
  //this is done for all pair (of source and target) u,v
  
  for(lemon::ListGraph::NodeIt n(g); n!=Invalid; ++n){
    for(lemon::ListGraph::NodeIt u(g); u!=Invalid; ++u){
      for(v(g) = u; v!=Invalid; ++v){
        
        //if n is the source, define the value of the flow
        if(n==u){
          
          //expre y is value of flow we loop over outarcs of n to create value of flow
          lemon::Lp::expr y;
          for(lemon::ListGraph::OutArcIt a(g,n); a!= Invalid; ++a)  y+=f[u][v][a];
          for(lemon::ListGraph::InArcIt a(g,n); a!= Invalid; ++a)  y-=f[u][v][a];

          //The value of the flow is equal to the number of internally vertex/edge? disjoint paths
          Lp.addrow(y >= g.id(v)-g.id(u));
        }
        else{
          if(n!=v){
            
            //conservation of flow constraint for all non source or target nodes.
            lemon::Lp::expr y;
            for(lemon::ListGraph::OutArcIt a(g,n); a!= Invalid; ++a)  y+=f[u][v][a];
            for(lemon::ListGraph::InArcIt a(g,n); a!= Invalid; ++a)  y-=f[u][v][a];
            Lp.addrow(y = 0);
          }
        }
      }
    }
  }
  

  //defining the objective function 
  Lp::expr obj;

  //cost of all arcs included is the objective functions
  for(lemon::ListGraph::EdgeIt e; e!=Invalid; ++e) obj+=x[e]*x[e];
  
  //minimization problem 
  lp.min();
  lp.obj(obj);
  lp.solve();
  
  //print results
  if (lp.primalType() == lemon::Lp::OPTIMAL) {
    
    //objective function value
    std::cout << "Objective function value: " << lp.primal() << std::endl;
    
    //print all edges and the corresponding x values
    for(lemon::ListGraph::EdgeIt e; e!=Invalid; ++e){
      std::cout << "x[" << e << "] = " << x[e] << std::endl;
    }
  }

  //When it doesn't
  else {
    std::cout << "Optimal solution not found." << std::endl;
  }



}
