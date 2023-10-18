#ifndef SCALE_FREE_NETWORK
#define SCALE_FREE_NETWORK

#include <iostream>
#include <vector>
#include <algorithm>
#include "network.h"

// 新节点加进来连接多少边
#define NEW_NODE_EDGE_COUNT 1

struct TFT_data_type {
    bool TFT = 0;
    double payoff = 0;
    std::vector<int> strategy;
    std::vector<int> prev_strategy;
};

struct scale_free_network : public __network__base<TFT_data_type> {
    scale_free_network(size_t network_node_count) {
        construct_network(network_node_count);
        init_network();
    }

    void construct_network(size_t network_node_count) {
        nodes.push_back(node());
        nodes.push_back(node());
        connect(0, 1);

        for (size_t i = 2; i < network_node_count; i++) {
            for (size_t add_count = 0; add_count < NEW_NODE_EDGE_COUNT; add_count++) {
                nodes.push_back(node());
                size_t current_node_index = nodes.size()-1;

                std::vector<double> degrees_table;
                for (size_t j = 0; j < current_node_index; j++) 
                    degrees_table.push_back(nodes[j].degrees());
                for (auto &j : degrees_table)
                    j /= degrees_sum();

                double rand = get_rand();

                size_t index = 0;
                for (auto j : degrees_table) {
                    rand -= j;
                    if (rand < 1e-6)
                        break;
                    index++;
                }
                
                connect(current_node_index, index);
            }
        }
    }

    void init_network() {
        
    }


};


#endif