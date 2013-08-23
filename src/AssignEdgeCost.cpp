#include "AssignEdgeCost.h"

//All cost are randomly generated integers from between 1 and some maximum m (through input double max)
void fill_cost_random(lemon::ListGraph::EdgeMap<double> *c, lemon::ListGraph *g , double max ){
  max = max + 0.5;
  int m = int(max);
  
  //Chosen integer costs as otherwise the solutions would be to trivial 
  //Randomly assign cost, (srand(time(0)) to prevent repetative cost patterns
  srand(time(0));
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e) (*c)[e] = rand() % m + 1;
}

//All cost the same
void fill_cost_constant(lemon::ListGraph::EdgeMap<double> *c , lemon::ListGraph *g, double  k ){
  for(lemon::ListGraph::EdgeIt e((*g)); e !=lemon::INVALID; ++e) (*c)[e] = k;
}

