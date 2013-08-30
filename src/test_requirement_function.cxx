#include "RequirementFunction.h"
#include "lemon/list_graph.h"

int main(){
   lemon::ListGraph g;
   //in for loop, fill nodes
   for(int i=0; i<4; i++){
      g.addNode();
   }
   RequirementFunction r;
   r.assignValue(g.nodeFromId(0),g.nodeFromId(1),2);
   std::cout << "We get value:" <<r.getValue(g.nodeFromId(0),g.nodeFromId(1)) << std::endl;
   std::cout << "We get value:" <<r.getValue(g.nodeFromId(1),g.nodeFromId(0)) << std::endl;

}
