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
Graph::Node a=g.addNode();
Graph::Node b=g.addNode();
g.addEdge(a,b);
Graph::EdgeMap< Lp::Col > x(g);

Lp lp;
lp.clear();
std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
lp.addColSet(x);
std::cout << "The number of columns="<<numberOfCols(lp)<< std::endl;
}
