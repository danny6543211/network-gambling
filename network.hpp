#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "rand.hpp"

namespace network {

using ID = unsigned int;

template<class NodeDataType>
struct __node {
    ID id;
    std::vector<ID> neighbors;
    NodeDataType data;

    __node(ID id) : id(id) {}

    size_t degree() const {
        return neighbors.size();
    }
};


struct __edge {
    ID source;
    ID target;

    __edge(ID source, ID target) 
    : source(source), target(target) {}
};


template<class NodeDataType>
struct __network__base
{
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
        nodes[x].neighbors.push_back(y);
        nodes[y].neighbors.push_back(x);
        edges.push_back(edge(x, y));
    }   

};


template<class NodeDataType>
struct BA_network : public __network__base<NodeDataType> {
    using node = typename __network__base<NodeDataType>::node;
    using edge = typename __network__base<NodeDataType>::edge;

    BA_network(size_t network_size, size_t new_node_edge_count) {
        this->add_node();
        this->add_node();
        this->connect(0, 1);
        
        for (size_t node_index = 2; node_index < network_size; node_index++) {
            for (size_t i = 0; i < new_node_edge_count; i++) {
                this->add_node();
                size_t new_node_index = node_index;
                std::vector<double> degree_table;
                for (size_t j = 0; j < new_node_index; j++) 
                    degree_table.push_back(this->nodes[j].degree() / (double) this->degree_of_network());

                double rand = get_rand_p();

                size_t connected_node_index = 0;
                for (auto j : degree_table) {
                    rand -= j;
                    if (rand < 1e-6)
                        break;
                    connected_node_index++;
                }

                this->connect(new_node_index, connected_node_index);
            }
        }
        
    }

};

}

#endif