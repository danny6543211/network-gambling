#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#include <deque>
#include "rand.h"

typedef size_t ID;

template<class NodeDataType>
struct __node {
    std::vector<ID> neighbors;
    NodeDataType data;

    size_t degrees() {
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
    typedef __node<NodeDataType>   node;
    typedef __edge                 edge;


    std::vector<node> nodes;
    std::vector<edge> edges;

    size_t network_degrees_sum() {
        size_t sum = 0;
        for (auto node : nodes)
            sum += node.neighbors.size();
        return sum;
    }

    void connect(ID x, ID y) {
        nodes[x].neighbors.push_back(y);
        nodes[y].neighbors.push_back(x);
        edges.push_back(edge(x, y));
    }
};

template<class NodeDataType>
struct __scale_free_network : public __network__base<NodeDataType> {
    typedef typename __network__base<NodeDataType>::node node;
    typedef typename __network__base<NodeDataType>::edge edge;

    __scale_free_network(size_t network_node_count, size_t new_node_edge_count) {
        this->nodes.push_back(node());
        this->nodes.push_back(node());
        this->connect(0, 1);
        
        for (size_t node_index = 2; node_index < network_node_count; node_index++) {
            for (size_t i = 0; i < new_node_edge_count; i++) {
                this->nodes.push_back(node());
                size_t new_node_index = node_index;
                std::vector<double> degrees_table;
                for (size_t j = 0; j < new_node_index; j++) 
                    degrees_table.push_back(this->nodes[j].degrees() / (double) this->network_degrees_sum());

                double rand = get_rand();

                size_t connected_node_index = 0;
                for (auto j : degrees_table) {
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


#endif