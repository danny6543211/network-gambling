#ifndef NETWORK_BASE
#define NETWORK_BASE

#include <memory>
#include <vector>

namespace ngl {

using ID = unsigned int;

struct NodeBase {
    NodeBase(ID id) : id(id) {}
    size_t degree() const { return neighbors.size(); }

    ID id;
    std::vector<ID> neighbors;
};

template<typename NodeDataType>
struct Node : public NodeBase {
    Node(ID id) : NodeBase(id) {}
    NodeDataType data;
};

struct Edge {
    Edge(ID source, ID target) : source(source), target(target) {}
    
    ID source;
    ID target;
};

template<typename NodeDataType>
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

    virtual void build(size_t arg1, size_t arg2) = 0;
protected:
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
    
    void ShrinkToFit() {
        this->nodes.shrink_to_fit();
        this->edges.shrink_to_fit();
    }

private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};

}   /* End of namespace ngl */

#endif