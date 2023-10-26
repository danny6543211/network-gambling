#ifndef NETWORK_BASE_HPP
#define NETWORK_BASE_HPP

#include <vector>

namespace ngl {

using ID = unsigned int;

template<class _NodeDataType>
struct NodeBase {
    using NodeDataType = _NodeDataType;
    
    ID id;
    NodeDataType data;
    NodeBase(ID id) : id(id) {}
};

template<class _NodeDataType>
struct GridNode : public NodeBase<_NodeDataType> {
    using NodeBase = NodeBase<_NodeDataType>;
    using NodeDataType = _NodeDataType;

    size_t degree() const { return 4; }
    GridNode(ID id) : NodeBase(id) {} 
};

template<class _NodeDataType>
struct RandomNode : public NodeBase<_NodeDataType> {
    using NodeBase = NodeBase<_NodeDataType>;
    using NodeDataType = _NodeDataType;

    std::vector<ID> neighbors;
    size_t degree() const { return neighbors.size(); }
    RandomNode(ID id) : NodeBase(id) {}
};

struct Edge {
    ID source;
    ID target;
    Edge(ID source, ID target) : source(source), target(target) {}
};

template<class _NodeType>
struct NetworkBase {
    using NodeType     = _NodeType;
    using NodeDataType = typename NodeType::NodeDataType;
    using Node         = NodeType;
    using Edge         = ngl::Edge;

    NodeType& operator[](ID id) { return nodes[id]; }
    Edge operator()(size_t i) { return edges[i]; }
    size_t degreesOfNetwork() {
        size_t sum = 0;
        for (auto const &node : nodes)
            sum += node.degree();
        return sum;
    }
    size_t networkSize() { return nodes.size(); }
    size_t edgeCount() { return edges.size(); }
protected:
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    void addNode() {
        nodes.push_back(Node(nodes.size()));
    }
    void addEdge(ID x, ID y) {
        edges.push_back(Edge(x, y));
    }
};


} /* End of namespace ng */

#endif