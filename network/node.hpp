#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template<class NodeDataType>
struct __node {
    using ID = unsigned int;

    ID id;
    std::vector<ID> neighbors;
    NodeDataType data;

    __node(ID id) : id(id) {}

    size_t degree() const {
        return neighbors.size();
    }
};

#endif