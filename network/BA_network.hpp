#ifndef BA_NETWORK_HPP
#define BA_NETWORK_HPP

#include <vector>
#include "network_base.hpp"
#include "rand.hpp"

namespace network {

template<class NodeDataType>
struct BA_network : public __network__base<NodeDataType> {
    using node = typename __network__base<NodeDataType>::node;
    using edge = typename __network__base<NodeDataType>::edge;

    BA_network(size_t network_node_count, size_t new_node_edge_count) {
        this->add_node();
        this->add_node();
        this->connect(0, 1);
        
        for (size_t node_index = 2; node_index < network_node_count; node_index++) {
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