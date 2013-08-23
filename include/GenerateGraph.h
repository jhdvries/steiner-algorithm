#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H
#include <lemon/list_graph.h>

void generate_complete_graph(lemon::ListGraph *, int);
void generate_incomplete_graph(lemon::ListGraph *, int);
void generate_peterson_graph(lemon::ListGraph *, int);

//These functions are used to create a type of the corresponding types.


#endif
