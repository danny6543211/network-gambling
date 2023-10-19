#ifndef SCALE_FREE_NETWORK
#define SCALE_FREE_NETWORK

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "network_base.h"

// 新节点加进来连接多少边
#define NEW_NODE_EDGE_COUNT 1

// #define BETRAY_STRATEGY     0
// #define COOPERATE_STRATEGY  1
// #define TFT_STRATEGY        2

enum class strategy {BETRAY, COOPERATE, TFT};
enum class behavior {BETRAY, COOPERATE};
strategy rand_strategy() { 
    return (strategy) (get_rand_int() % 3);
}
behavior rand_behavior() {
    return (behavior) (get_rand_int() % 2);
}

struct TFT_data_type {
    strategy strategy;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::unordered_map<ID, behavior> neighbors_impression;
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
                ID x = edge.source;
                ID y = edge.target;
                behavior x_behavior;
                behavior y_behavior;
                
                // two TFT
                if (nodes[x].data.strategy == strategy::TFT && nodes[y].data.strategy == strategy::TFT) {
                    x_behavior = nodes[x].data.neighbors_impression[y];
                    y_behavior = nodes[y].data.neighbors_impression[x];
                }
                // no TFT
                else if (nodes[x].data.strategy != strategy::TFT && nodes[y].data.strategy != strategy::TFT) {
                    x_behavior = (behavior) nodes[x].data.strategy;
                    y_behavior = (behavior) nodes[y].data.strategy;
                }
                // one TFT
                else {
                    if (nodes[x].data.strategy == strategy::TFT) {
                        x_behavior = nodes[x].data.neighbors_impression[y];
                        y_behavior = (behavior) nodes[y].data.strategy;
                    }
                    else {
                        x_behavior = (behavior) nodes[x].data.strategy;
                        y_behavior = nodes[y].data.neighbors_impression[x];
                    }
                }

                battle(x, x_behavior, y, y_behavior, this_tern_payoff, r);
            }
        }

        // 更新收益
        for (size_t i = 0; i < this_tern_payoff.size(); i++) {
            nodes[i].data.this_tern_payoff = this_tern_payoff[i];
            nodes[i].data.payoff += nodes[i].data.this_tern_payoff;
        }
    }

    void opitimize() {
        std::vector<int> this_tern_strategy(nodes.size(), -1);
        
        for (size_t source_ID = 0; source_ID < nodes.size(); source_ID++) {
            std::vector<double> degrees_table;
            size_t neighbors_degrees_sum = 0;
            for (auto neighbor_ID : nodes[source_ID].neighbors) {
                size_t neighbor_degrees = nodes[neighbor_ID].degrees();
                degrees_table.push_back(neighbor_degrees);
                neighbors_degrees_sum += neighbor_degrees;
            }
            // 把 度/邻居所有度 转换为概率
            for (auto &i : degrees_table)
                i /= (double) neighbors_degrees_sum;

            double rand = get_rand();
            size_t target_neighbor_index = 0;
            for (auto degrees_p : degrees_table) {
                rand -= degrees_p;
                if (rand < 1e-6)
                    break;
                target_neighbor_index++;
            }
            ID target_ID = nodes[source_ID].neighbors[target_neighbor_index];

            if (nodes[source_ID].data.strategy == nodes[target_ID].data.strategy)
                continue;

            double p = 1 / (1 + exp((nodes[source_ID].data.this_tern_payoff - nodes[target_ID].data.this_tern_payoff) / 0.01));
            rand = get_rand();

            if (p > rand)
                this_tern_strategy[source_ID] = (int) nodes[target_ID].data.strategy;
        }

        // 更新策略
        for (size_t i = 0; i < this_tern_strategy.size(); i++) {
            if (this_tern_strategy[i] == -1)
                continue;
            nodes[i].data.strategy = (strategy) this_tern_strategy[i];
        }
    }

    void export_node_status(std::string file_path) {
        std::ofstream file(file_path, std::ios::out);
        
        file << "degrees,strategy,payoff" << "\n";
        for (auto node : nodes) {
            file << node.degrees() << ",";
            file << (int) node.data.strategy << ",";
            file << node.data.payoff << "\n";
        } 

        file.close();
    }

private:
    void construct_network(size_t network_node_count) {
        nodes.push_back(node());
        nodes.push_back(node());
        connect(0, 1);
        
        for (size_t node_index = 2; node_index < network_node_count; node_index++) {
            for (size_t i = 0; i < NEW_NODE_EDGE_COUNT; i++) {
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

    void init_network() {
        for (auto &node : nodes) {
            // 网络初始化为对自己随机策略，对邻居随机印象
            node.data.strategy = rand_strategy();
            for (size_t j = 0; j < node.neighbors.size(); j++) {
                node.data.neighbors_impression[node.neighbors[j]] = rand_behavior();
            }
        }
    }

    // 雪堆博弈
    void battle(ID x, behavior x_behavior, ID y, behavior y_behavior, 
    std::vector<double>& payoff, double r) {
        if (x_behavior == y_behavior) {
            // ALL COOPERATE
            if (x_behavior == behavior::COOPERATE) {
                payoff[x] += 1;
                payoff[y] += 1;
            }
            // All BETRAY
            else 
                ;
        }
        else {
            // x: COOPERATE   y: BETRAY
            if (x_behavior == behavior::COOPERATE) {
                payoff[x] += 1 - r;
                payoff[y] += 1 + r;
            }
            // x: BETRAY   y: COOPERATE
            else {
                payoff[x] += 1 + r;
                payoff[y] += 1 - r;
            }
        }
    }
};


#endif