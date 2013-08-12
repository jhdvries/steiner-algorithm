#include "RequirementFunction.h"

void RequirementFunction::assignValue(lemon::ListGraph::Node u,lemon::ListGraph::Node v,int value){
   _requirement_function[std::make_pair(u,v)]=value; 
   _requirement_function[std::make_pair(v,u)]=value; 
}

int RequirementFunction::getValue(lemon::ListGraph::Node u,lemon::ListGraph::Node v){
   return  _requirement_function[std::make_pair(u,v)];
}
