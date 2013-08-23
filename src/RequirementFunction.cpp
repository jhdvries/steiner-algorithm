#include "RequirementFunction.h"

void RequirementFunction::assignValue(lemon::ListGraph::Node u,lemon::ListGraph::Node v,int value){
   _requirement_function[std::make_pair(u,v)]=value; 
   _requirement_function[std::make_pair(v,u)]=value; 
}

int RequirementFunction::getValue(lemon::ListGraph::Node u,lemon::ListGraph::Node v){
   return  _requirement_function[std::make_pair(u,v)];
}

//This is a purely technical procedure in order to be able to define flow variables.
//There was no template in the lemon library fore a edgemap for every set of nodes. 
