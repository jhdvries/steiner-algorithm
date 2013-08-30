#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/glpk.h>
#include <lemon/lp.h>

int main(){
  lemon::Lp lp;
  lemon::ListGraph g;
  //define graph
  lemon::ListGraph::Node source = g.addNode();
  lemon::ListGraph::Node target = g.addNode();
  for(int i=0; i<4; i++){
      g.addNode();
   }
   //now in a double for loop attach edges
   //let u start at the beginning of the graph;
    for (lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID ;++u){
       //let v start from u
       for (lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID ;++v){
          if(u!=v){ 
             lemon::ListGraph::Edge temp_edge= g.addEdge(u,v);
                                              
             //assigns cost function
             std::cout << "Added edge with ids u: " << g.id(u) << " v: " <<  g.id(v) << std::endl;
          }
          else{
            std::cout << "Didn't make node, because the Nodes were the same" << std::endl; 
          }
        }
  }
  // Add a column to the problem for each arc
  lemon::ListGraph::EdgeMap<lemon::Lp::Col> f(g);
  lp.addColSet(f);
  // Capacity constraints
  for (lemon::ListGraph::EdgeIt a(g); a != lemon::INVALID; ++a) {
        lp.colLowerBound(f[a], 0);
        lp.colUpperBound(f[a], 1);
    }
  // Flow conservation constraints
  for (lemon::ListGraph::NodeIt n(g); n != lemon::INVALID; ++n) {
        if (n == source || n == target) continue;
        lemon::Lp::Expr e;
        for (lemon::ListGraph::OutArcIt a(g, n); a != lemon::INVALID; ++a) e += f[a];
        for (lemon::ListGraph::InArcIt a(g, n); a != lemon::INVALID; ++a) e -= f[a];
        lp.addRow(e == 0);
    }
  // Objective function
  lemon::Lp::Expr o;
  for (lemon::ListGraph::OutArcIt a(g, source); a != lemon::INVALID; ++a) o += f[a];
  for (lemon::ListGraph::InArcIt a(g, source); a != lemon::INVALID; ++a) o -= f[a];
  lp.max();
  lp.obj(o);
  // Solve the LP problem
  if (lp.primalType() == lemon::Lp::OPTIMAL) {
      std::cout << "Objective function value: " << lp.primal() << std::endl;
    }
    else {
    std::cout << "Optimal solution not found." << std::endl;
    }
  if (lp.primalType() == lemon::Lp::UNDEFINED) {
      std::cout << "GODVER, ongedefinieerd" << lp.primal() << std::endl;
    }
    else {
    std::cout << "GELUKKIG, HIJ IS GEDEFINIEERD" << std::endl;
    }
}
