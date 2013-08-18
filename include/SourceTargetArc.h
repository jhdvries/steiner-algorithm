#ifndef SOURCETARGETEDGE
#define SOURCETARGETEDGE
#include <lemon/list_graph.h>

class SourceTargetEdge{
    public:
        SourceTargetEdge(){}
        SourceTargetEdge(lemon::ListGraph::Node,lemon::ListGraph::Node,lemon::ListGraph::Edge);
        ~SourceTargetEdge(){}
        bool operator < (const SourceTargetEdge ste1) const;
    private:
        lemon::ListGraph::Node _source;
        lemon::ListGraph::Node _target;
        lemon::ListGraph::Edge _edge;
};

#endif
