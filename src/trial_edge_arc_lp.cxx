#include <lemon/glpk.h>
#include <lemon/lp.h>

int main(){
  lemon::Lp lp;
  lemon::ListGraph g;
  //define graph
  lemon::ListGraph source = g.addNode();
  lemon::ListGraph target = g.addNode();
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
  lemon::ListGraph EdgeMap<Lp::Col> f(g);
  lp.addColSet(f);
  // Capacity constraints
  for (EdgeIt a(g); a != INVALID; ++a) {
        lp.colLowerBound(f[a], 0);
        lp.colUpperBound(f[a], capacity[a]);
    }
  // Flow conservation constraints
  for (NodeIt n(g); n != INVALID; ++n) {
        if (n == source || n == target) continue;
        Lp::Expr e;
        for (OutEdgeIt a(g, n); a != INVALID; ++a) e += f[a];
        for (InEdgeIt a(g, n); a != INVALID; ++a) e -= f[a];
        lp.addRow(e == 0);
    }
  // Objective function
  Lp::Expr o;
  for (OutEdgeIt a(g, source); a != INVALID; ++a) o += f[a];
  for (InEdgeIt a(g, source); a != INVALID; ++a) o -= f[a];
  lp.max();
  lp.obj(o);
  // Solve the LP problem
  lp.solve();
}
