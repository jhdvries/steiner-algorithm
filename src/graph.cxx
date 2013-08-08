#include <iostream> 
#include <lemon/list_graph.h>

int main(){
   lemon::ListGraph g;
   int i = 1;
   std::cout << "so far so good, now the for loop" << i << std::endl;
   for( i = 1; i<= 4; i++){
     g.addNode();
     std::cout << "we have node: " <<  i  << std::endl:
     int j = 1;
     while(j!=i){   
        g.addEdge(i,j);
        std::cout << "now we have edge: " << k << std:: endl;
        j++;
     }
   return 0;
}


