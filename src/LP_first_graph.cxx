#include <lemon/list_graph.h>
#include <lemon/glpk.h>
using namespace lemon;

typedef GlpkLp Lp;

///Query function about the LP
int numberOfCols(Lp & lp) {
int count=0;
for (Lp::ColIt c(lp); c!=lemon::INVALID; ++c) ++count;
return count;
}

int main(){
   typedef lemon::ListGraph Graph;
   Graph g;
   //in for loop, fill nodes
   Graph::EdgeMap<int> cost(g);
   Graph::NodeMap<int> req(g);
   for(int i=0; i<4; i++){
      Graph::Node temp_node=g.addNode();
      req[temp_node]=3; 
   }
   //now in a double for loop attach edges
   //let u start at the beginning of the graph;
   for (Graph::NodeIt u(g); u!=lemon::INVALID ;++u){
      //let v start from u
      for (Graph::NodeIt v(u); v!=lemon::INVALID ;++v){
         if(u!=v){ 
            Graph::Edge temp_edge= g.addEdge(u,v);
            
            //assigns cost function
            cost[temp_edge]=3;
            std::cout << "Added edge with ids u: " << g.id(u) << " v: " <<  g.id(v) << std::endl;
         }
         else{
            std::cout << "Didn't make node, because the Nodes were the same" << std::endl; 
         }
      }
   }

   // assign LP colum variables to edges 
   Graph::EdgeMap< Lp::Col > x(g);

    Lp lp;
    lp.clear();
    std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
    lp.addColSet(x);
    std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
   
    //add constraints each node has at least one outgoing arc
    lp.addRow( x[Graph::edgeFromId(1)] + x[Graph::edgeFromId(2)] + x[Graph::edgeFromId(3)] >= 1);
    lp.addRow( x[Graph::edgeFromId(1)] + x[Graph::edgeFromId(4)] + x[Graph::edgeFromId(5)] >= 1);
    lp.addRow( x[Graph::edgeFromId(2)] + x[Graph::edgeFromId(4)] + x[Graph::edgeFromId(6)] >= 1);
    lp.addRow( x[Graph::edgeFromId(5)] + x[Graph::edgeFromId(3)] + x[Graph::edgeFromId(6)] >= 1);
    
    //add lowerbounds on variables
    lp.colLowerBound(x[Graph::edgeFromId(1)], 0);
    lp.colLowerBound(x[Graph::edgeFromId(2)], 0);
    lp.colLowerBound(x[Graph::edgeFromId(3)], 0);
    lp.colLowerBound(x[Graph::edgeFromId(4)], 0);
    lp.colLowerBound(x[Graph::edgeFromId(5)], 0);
    lp.colLowerBound(x[Graph::edgeFromId(6)], 0);
    
    //add objective function
    lp.min();

     lp.obj(cost[Graph::edgeFromId(1)]*x[Graph::edgeFromId(1)]+cost[Graph::edgeFromId(2)]*x[Graph::edgeFromId(2)]+cost[Graph::edgeFromId(3)]*x[Graph::edgeFromId(3)]+cost[Graph::edgeFromId(4)]*x[Graph::edgeFromId(4)]+cost[Graph::edgeFromId(5)]*x[Graph::edgeFromId(5)]+cost[Graph::edgeFromId(6)]*x[Graph::edgeFromId(6)]);

    //solve the LP
    lp.solve();

    //print results
    // Print the results
  if (lp.primalType() == Lp::OPTIMAL) {
      std::cout << "Objective function value: " << lp.primal() << std::endl;
      std::cout << "x1 = " << lp.primal(x[Graph::edgeFromId(1)]) << std::endl;
      std::cout << "x2 = " << lp.primal(x[Graph::edgeFromId(2)]) << std::endl;
      std::cout << "x3 = " << lp.primal(x[Graph::edgeFromId(3)]) << std::endl;
      std::cout << "x4 = " << lp.primal(x[Graph::edgeFromId(4)]) << std::endl;
      std::cout << "x5 = " << lp.primal(x[Graph::edgeFromId(5)]) << std::endl;
      std::cout << "x6 = " << lp.primal(x[Graph::edgeFromId(6)]) << std::endl;
    }
    else {
    std::cout << "Optimal solution not found." << std::endl;
    }
}
