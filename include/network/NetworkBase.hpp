#pragma once 

#include <vector>
#include "Node.hpp"
#include "Edge.hpp"

namespace ngl {

template<class NodeDataType>
struct NetworkBase {
    using Node = Node<NodeDataType>;

    Node& operator[](ID id) {
        return nodes[id];
    }

    Edge operator()(size_t i) {
        return edges[i];
    }

    size_t networkSize() const {
        return nodes.size();
    }

    size_t edgeCount() const {
        return edges.size();
    }

    void addNode() {
        nodes.push_back(Node(nodes.size()));
    }
    
    void addEdge(ID x, ID y) {
        edges.push_back(Edge(x, y));
    }

    size_t degreesOfNetwork() {
        size_t sum = 0;
        for (auto const &node : nodes)
            sum += node.degree();
        return sum;
    }
// private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};


}   /* End of namespace ngl */