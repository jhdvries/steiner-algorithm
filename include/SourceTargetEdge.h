#ifndef SOURCETARGETEDGE
#define SOURCETARGETEDGE
#include <lemon/list_graph.h>

class SourceTargetEdge{
    public:
        SourceTargetEdge(){}
        SourceTargetEdge(lemon::ListGraph::Node,lemon::ListGraph::Node,lemon::ListGraph::Edge);
        ~SourceTargetEdge(){}
    private:
        lemon::ListGraph::Node _source;
        lemon::ListGraph::Node _target;
        lemon::ListGraph::Edge _edge;
};

#endif
