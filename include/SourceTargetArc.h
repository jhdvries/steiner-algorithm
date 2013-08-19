#ifndef SOURCETARGETARC
#define SOURCETARGETARC
#include <lemon/list_graph.h>

///FIXME: had to introduce a hack to enable usage in std::map, using the graph and the node and edge ids to 
/// generate an int
class SourceTargetArc{
    public:
        SourceTargetArc(){}
        SourceTargetArc(lemon::ListGraph*, lemon::ListGraph::Node,lemon::ListGraph::Node,lemon::ListGraph::Arc);
        ~SourceTargetArc(){}
        bool operator < (const SourceTargetArc &) const;
        int id();
    private:
        lemon::ListGraph::Node _source;
        lemon::ListGraph::Node _target;
        lemon::ListGraph::Arc _arc;
        lemon::ListGraph* _graph;
};

#endif
