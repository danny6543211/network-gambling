#pragma once 

#include "Node.hpp"

namespace ngl {

struct Edge {
    Edge(ID source, ID target) : source(source), target(target) {}
    
    ID source;
    ID target;
};

}   /* End of namespace ngl */