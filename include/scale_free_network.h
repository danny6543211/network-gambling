#ifndef SCALE_FREE_NETWORK
#define SCALE_FREE_NETWORK

#include <iostream>
#include "network_base.h"

namespace network {

template<class NodeDataType>
struct scale_free_network : public __network__base<NodeDataType> {

    scale_free_network(size_t network_node_count, size_t new_node_edge_count) {
        construct_network(network_node_count, new_node_edge_count);
        init();
    }

    void construct_network(size_t network_node_count, size_t new_node_edge_count) {
        nodes.push_back(node());
        nodes.push_back(node());
        connect(0, 1);
        
        for (size_t node_index = 2; node_index < network_node_count; node_index++) {
            for (size_t i = 0; i < new_node_edge_count; i++) {
                nodes.push_back(node());
                size_t new_node_index = node_index;
                std::vector<double> degrees_table;
                for (size_t j = 0; j < new_node_index; j++) 
                    degrees_table.push_back(nodes[j].degrees() / (double) network_degrees_sum());

                double rand = get_rand();

                size_t connected_node_index = 0;
                for (auto j : degrees_table) {
                    rand -= j;
                    if (rand < 1e-6)
                        break;
                    connected_node_index++;
                }

                connect(new_node_index, connected_node_index);
            }
        }
    }

    void gambling(size_t caculate_count) {
        for (size_t i = 0; i < caculete_count; i++) {
            caculate();
        }
        optimize();
    }
    
    virtual void init();

    virtual void caculate();

    virtual void optimize();

};

}

#endif