#include "SourceTargetEdge.h"

SourceTargetEdge::SourceTargetEdge(lemon::ListGraph::Node source,lemon::ListGraph::Node target,lemon::ListGraph::Edge edge):
    _source(source), _target(target), _edge(edge)
{
    //deliberatley emtpy
}
