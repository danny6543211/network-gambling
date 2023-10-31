#pragma once

#include <cstdlib>
#include <vector>

namespace ngl {

using ID = unsigned int;

template<class NodeDataType>
struct Node {
    Node(ID x) : id(x) {}
    size_t degree() const { return neighbors.size(); }

    ID id;
    std::vector<ID> neighbors;
};


}   /* End of namespace ngl */