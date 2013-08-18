#include "SourceTargetEdge.h"

SourceTargetEdge::SourceTargetEdge(lemon::ListGraph::Node source,lemon::ListGraph::Node target,lemon::ListGraph::Edge edge):
    _source(source), _target(target), _edge(edge)
{
    //deliberatley emtpy
}

//NOTE: This a dummy operator, which is only introduced as it is required by std::map
bool SourceTargetEdge::operator < ( SourceTargetEdge ste) const{
    return (_source<ste._source);
}
