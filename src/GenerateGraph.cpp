#include "GenerateGraph.h"
#include <lemon/maps.h>

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


void generate_incomplete_graph(lemon::ListGraph *g, int N){
  for(int i=0; i<N; i++){
    g->addNode();
  }
  
  srand(time(0));

  //create edges to make graph complete and assigning cost to edges
  for (lemon::ListGraph::NodeIt u(*g); u!=lemon::INVALID ;++u){
    for (lemon::ListGraph::NodeIt v(u); v!=lemon::INVALID ;++v){
      if(u!=v){
        //initialise edge (uv)
        int randomval = rand() % 2;
        if(randomval== 0)
        g->addEdge(u,v);
      }
    }
  }
}


 void generate_peterson_graph(lemon::ListGraph *g, int N){
 //create 10 nodes
 for(int i=0; i<10; i++){
    g->addNode();
 }
 
 //making degree map
 lemon::ListGraph::NodeMap<int> d((*g));
 for (lemon::ListGraph::NodeIt u(*g); u!=lemon::INVALID ;++u) d[u]=0;

  std::cout<<"nodes initialised"<< std::endl;

 //create the edges that are required
 g->addEdge(lemon::ListGraph::nodeFromId(0),lemon::ListGraph::nodeFromId(1));
 g->addEdge(lemon::ListGraph::nodeFromId(0),lemon::ListGraph::nodeFromId(4));
 g->addEdge(lemon::ListGraph::nodeFromId(0),lemon::ListGraph::nodeFromId(7));
 g->addEdge(lemon::ListGraph::nodeFromId(1),lemon::ListGraph::nodeFromId(2));
 g->addEdge(lemon::ListGraph::nodeFromId(1),lemon::ListGraph::nodeFromId(5));
 g->addEdge(lemon::ListGraph::nodeFromId(2),lemon::ListGraph::nodeFromId(3));
 g->addEdge(lemon::ListGraph::nodeFromId(2),lemon::ListGraph::nodeFromId(9));
 g->addEdge(lemon::ListGraph::nodeFromId(3),lemon::ListGraph::nodeFromId(4));
 g->addEdge(lemon::ListGraph::nodeFromId(3),lemon::ListGraph::nodeFromId(6));
 g->addEdge(lemon::ListGraph::nodeFromId(4),lemon::ListGraph::nodeFromId(8));
 g->addEdge(lemon::ListGraph::nodeFromId(5),lemon::ListGraph::nodeFromId(6));
 g->addEdge(lemon::ListGraph::nodeFromId(5),lemon::ListGraph::nodeFromId(8));
 g->addEdge(lemon::ListGraph::nodeFromId(6),lemon::ListGraph::nodeFromId(7));
 g->addEdge(lemon::ListGraph::nodeFromId(7),lemon::ListGraph::nodeFromId(9));
 g->addEdge(lemon::ListGraph::nodeFromId(8),lemon::ListGraph::nodeFromId(9));

  
}
