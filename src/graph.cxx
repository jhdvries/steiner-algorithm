#include <iostream> 
#include <vector>
#include <lemon/list_graph.h>

int main(){
   //NOTE: this script is just a demonstration of how one could go about this. 
   //Maybe there are better ways though
   lemon::ListGraph g;
   //Want to keep list of "lemon::ListGraph::Node"s
   std::vector<lemon::ListGraph::Node> my_nodes;
   //in for loop, fill nodes
   for(int i=0; i<4; i++){
      my_nodes.push_back(g.addNode());
      std::cout << "we have node: " <<  i  << std::endl;
   }
   //now in a double for loop attach edges
   for(int j=0;j<4;j++){
       for(int k=j+1;k<4;k++){
          std::cout << "making edges from node " << j << " to " << k << std::endl;
          g.addEdge(my_nodes[j],my_nodes[k]);
       }
   }
   return 0;
}


