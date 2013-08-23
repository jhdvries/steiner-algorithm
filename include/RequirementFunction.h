#ifndef REQUIREMENTFUNCTION_H
#define REQUIREMENTFUNCTION_H
#include <utility> 
#include <map>
#include "lemon/list_graph.h"


class RequirementFunction{
    public:
        RequirementFunction(){};
        ~RequirementFunction(){};
        void assignValue(lemon::ListGraph::Node,lemon::ListGraph::Node,int);
        int getValue(lemon::ListGraph::Node,lemon::ListGraph::Node);
    private:
        std::map< std::pair< lemon::ListGraph::Node , lemon::ListGraph::Node > , int> _requirement_function;
};

//Technical necessity for indexing the flow variables
#endif
