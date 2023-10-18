#ifndef SCALE_FREE_NETWORK
#define SCALE_FREE_NETWORK

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "network.h"

// 新节点加进来连接多少边
#define NEW_NODE_EDGE_COUNT 1

#define BETRAY              0
#define COOPERATE           1
#define TFT_STRATEGY        2

struct TFT_data_type {
    bool TFT = 0;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::vector<int> strategy;
    std::vector<int> prev_strategy;
};

struct scale_free_network : public __network__base<TFT_data_type> {
    scale_free_network(size_t network_node_count) {
        construct_network(network_node_count);
        init_network();
    }

    void caculate(size_t caculate_count, double r) {
        std::vector<double> this_tern_payoff(nodes.size(), 0);
        for (size_t i = 0; i < caculate_count; i++) {
            for (auto edge : edges) {
                int x = edge.source;
                int y = edge.target;
                
                bool x_strategy = -1;
                bool y_strategy = -1;

                // two TFT
                if (nodes[x].data.TFT == true && nodes[y].data.TFT == true) {
                    size_t y_offset = std::find(nodes[x].neighbors.begin(), 
                    nodes[x].neighbors.end(), &nodes[y]) - nodes[x].neighbors.begin();

                    size_t x_offset = std::find(nodes[y].neighbors.begin(), 
                    nodes[y].neighbors.end(), &nodes[x]) - nodes[y].neighbors.begin();

                    bool x_strategy = nodes[x].neighbors[y_offset]->data.prev_strategy[0];
                    bool y_strategy = nodes[y].neighbors[x_offset]->data.prev_strategy[0];
                }
                // no TFT
                else if (nodes[x].data.TFT == false && nodes[y].data.TFT == false) {
                    x_strategy = nodes[x].data.strategy[0];
                    y_strategy = nodes[y].data.strategy[0];
                }
                // one TFT
                else {
                    // x is TFT
                    if (nodes[x].data.TFT == true) {
                        size_t y_offset = std::find(nodes[x].neighbors.begin(), 
                        nodes[x].neighbors.end(), &nodes[y]) - nodes[x].neighbors.begin();

                        bool x_strategy = nodes[x].neighbors[y_offset]->data.prev_strategy[0];
                        bool y_strategy = nodes[y].data.strategy[0];
                    }
                    // y is TFT
                    else {
                        size_t x_offset = std::find(nodes[y].neighbors.begin(), 
                        nodes[y].neighbors.end(), &nodes[x]) - nodes[y].neighbors.begin();

                        bool x_strategy = nodes[x].data.strategy[0];
                        bool y_strategy = nodes[y].neighbors[x_offset]->data.prev_strategy[0];
                    }
                }

                battle(x, x_strategy, y, y_strategy, this_tern_payoff, r);
            }
        }
        for (size_t i = 0; i < nodes.size(); i++) {
            nodes[i].data.this_tern_payoff = this_tern_payoff[i];
            nodes[i].data.payoff += this_tern_payoff[i];
        }
    }

    void opitimize() {
        
    }

    void export_node_status(std::string file_path) {
        std::ofstream file(file_path, std::ios::out);
        
        file << "degrees,strategy,payoff" << "\n";

        for (auto node : nodes) {
            file << node.degrees() << ",";

            if (node.data.TFT == true)
                file << TFT_STRATEGY << ",";
            else 
                file << node.data.strategy[0] << ",";

            file << node.data.payoff << "\n";
        } 

        file.close();
    }

private:
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
                    degrees_table.push_back(nodes[j].degrees() / (double) degrees_sum());

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
        for (auto &node : nodes) {
            // initailize prev_strategy and strategy 
            for (size_t i = 0; i < node.degrees(); i++) {
                node.data.prev_strategy.push_back(-1);
                node.data.strategy.push_back(-1);
            }

            // '3' it means Cooperate, Betray, and TFT
            int rand_strategy = get_rand_int() % 3;
            if (rand_strategy == TFT_STRATEGY) {
                node.data.TFT = true;
                for (auto &i : node.data.prev_strategy)
                    i = get_rand_int() % 2; /* Cooperate and Betray */
                node.data.strategy = node.data.prev_strategy;
            }
            else {
                node.data.prev_strategy[0] = rand_strategy;
                node.data.strategy[0] = rand_strategy;
            }
        }
    }

    // 雪堆博弈
    void battle(size_t x, bool x_strategy, size_t y, bool y_strategy, 
    std::vector<double>& payoff, double r) {
        if (x_strategy == y_strategy) {
            if (x_strategy == COOPERATE) {
                payoff[x] += 1;
                payoff[y] += 1;
            }
        }
        else {
            if (x_strategy == COOPERATE) {
                payoff[x] += 1 - r;
                payoff[y] += 1 + r;
            }
            else {
                payoff[x] += 1 + r;
                payoff[y] += 1 - r;
            }
        }
    }
};




#endif