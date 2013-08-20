#include "GenerateGraph.h"

void generate_complete_graph(lemon::ListGraph *g, int N){
  for(int i=0; i<N; i++){
    g->addNode();
  }

  //create edges to make graph complete and assigning cost to edges
  for (lemon::ListGraph::NodeIt u(*g); u!=lemon::INVALID ;++u){
    for (lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID ;++v){
      if(u!=v){
        //initialise edge (uv)
        g->addEdge(u,v);
      }
    }
  }
    
}
