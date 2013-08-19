#include "SourceTargetArc.h"

SourceTargetArc::SourceTargetArc(lemon::ListGraph*g,lemon::ListGraph::Node source,lemon::ListGraph::Node target,lemon::ListGraph::Arc arc):
   _graph(g), _source(source), _target(target), _arc(arc)
{
    //deliberatley emtpy
}

int SourceTargetArc::id(){
    int maxN=_graph->maxNodeId()+1;
    int maxA=_graph->maxArcId()+1;
    return _graph->id(_source)+ maxN*_graph->id(_target)+ maxN*maxA*_graph->id(_arc);
}

//NOTE: This a dummy operator, which is only introduced as it is required by std::map
bool SourceTargetArc::operator < ( const SourceTargetArc & sta) const{
    if (_target<sta._target) return true;
    else if (_source<sta._source) return true;
    else if (_arc<sta._arc) return true;
    else return false;
}
