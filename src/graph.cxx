#include <iostream> 
#include <lemon/list_graph.h>
#include <lemon/concepts/graph.h>

int main(){
   lemon::ListGraph g;
   std::cout << "so far so good, now the for loop" << std::endl;
   for(int  i = 0; i< 4; i++){
     g.addNode();
     std::cout << "we have another node: " << i  << std::endl;}
   for (lemon::listGraph::NodeIt n(g); n != INVALID; ++n){
     for (lemon::listGraph::NodeIt m(g); m!=INVALID; ++m){
        g.addEdge(n,m);
        std::cout<< "we have an edge from " << n << " to " << m << std::endl; }}
   return 0;
}


