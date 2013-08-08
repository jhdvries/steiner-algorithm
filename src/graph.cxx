#include <iostream> 
#include <vector>
#include <lemon/list_graph.h>

int main(){
   lemon::ListGraph g;
   //in for loop, fill nodes
   for(int i=0; i<4; i++){
      lemon::ListGraph::Node temp_node=g.addNode();
      std::cout << "we created node with id: " <<  g.id(temp_node)  << std::endl;
   }
   //now in a double for loop attach edges
   //let u start at the beginning of the graph
   for (lemon::ListGraph::NodeIt u(g); u!=lemon::INVALID ;++u){
      //let v start from u
      for (lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID ;++v){
         if(u!=v){ 
             g.addEdge(u,v);
             std::cout << "Added edge with ids u: " << g.id(u) << " v: " << g.id(v) << std::endl;
         }
         else{
            std::cout << "Didn't make node, because the Nodes were the same" << std::endl; 
         }
      }
   }
   return 0;
}


