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
   //let u start at the beginning of the graph
   for (Graph::NodeIt u(g); u!=lemon::INVALID ;++u){
      //let v start from u
      for (Graph::NodeIt v(u); v!=lemon::INVALID ;++v){
         if(u!=v){ 
            Graph::Edge temp_edge= g.addEdge(u,v);
            cost[temp_edge]=3;
            std::cout << "Added edge with ids u: " << g.id(u) << " v: " <<  g.id(v) << std::endl;
         }
         else{
            std::cout << "Didn't make node, because the Nodes were the same" << std::endl; 
         }
      }
   }
   Graph::EdgeMap< Lp::Col > x(g);

    Lp lp;
    lp.clear();
    std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
    lp.addColSet(x);
    std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
}
