#include "AssignEdgeCost.h"

//All cost are randomly generated from a ... distribution
void fill_cost_random(lemon::ListGraph::EdgeMap<int> *c, lemon::ListGraph *g ){
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e) (*c)[e] = rand() % 10;
}

//All cost are of the integer value u
void fill_cost_constant(lemon::ListGraph::EdgeMap<int> *c , lemon::ListGraph *g, int k ){
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e) (*c)[e] = k;
}

//All cost are of the integer value u
//void fill_cost_constant(lemon::ListGraph::EdgeMap<int> *c, lemon::ListGraph *g){
//  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e){
//    if((*g).id(lemon::ListGraph::Node u(e))>(*g)g.id(lemon::ListGraph::Node v(e))) (*c)[e]=(*g).id(lemon::ListGraph::Node u(e))-(*g).id(lemon::ListGraph::Node v(e));
//    else (*c)[e]=(*g).id(lemon::ListGraph::Node v(e))-(*g).id(lemon::ListGraph::Node u(e));
//  }
//}
