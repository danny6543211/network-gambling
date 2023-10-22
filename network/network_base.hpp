#ifndef NETWORK_BASE_HPP
#define NETWORK_BASE_HPP

#include <vector>
#include "node.hpp"
#include "edge.hpp"

template<class NodeDataType>
struct __network__base
{
    using ID   = unsigned int;
    using node = __node<NodeDataType>;
    using edge = __edge;

    std::vector<node> nodes;    /* Index of nodes is ID */
    std::vector<edge> edges;

    size_t degree_of_network() {
        size_t sum = 0;
        for (auto const &node : nodes)
            sum += node.degree();
        return sum;
    }

    void add_node() {
        nodes.push_back(node(nodes.size()));
    }

    void connect(ID x, ID y) {
        nodes[x].neighbors.insert(y);
        nodes[y].neighbors.insert(x);
        edges.push_back(edge(x, y));
    }   

};

#endif