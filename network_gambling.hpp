#ifndef NETWORK_GAMBLING_HPP
#define NETWORK_GAMBLING_HPP


#include <unordered_map>
#include <memory>
#include "network.hpp"
#include "gambling.hpp"
#include "rand.hpp"

namespace ng {

struct node_data {
    using ID = network::ID;

    gambling::strategy strategy = gambling::strategy::COOPERATION;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::unordered_map<ID, gambling::behavior> neighbors_impression;
};


class network_gambling {
public:
    using ID              = network::ID;
    using network_type    = network::BA_network<node_data>;
    using strategy        = gambling::strategy;
    using behavior        = gambling::behavior;
    using gambling_method = gambling::gambling_method;

    std::unique_ptr<network_type> network;

private:
    gambling_method gambling_type        = gambling_method::prisoners_dilemma;   
    size_t network_size                  = 200;
    size_t new_node_edge_count           = 1;
    size_t one_iteration_caculate_count  = 1;
    double r                             = 0; 

public:
    network_gambling() { build_network(); }
    network_gambling(double r) : r(r) { build_network(); }

    network_gambling(size_t network_size, size_t new_node_edge_count, 
    size_t one_iteration_caculate_count, double r) 
    : 
    network_size(network_size), 
    new_node_edge_count(new_node_edge_count), 
    one_iteration_caculate_count(one_iteration_caculate_count), 
    r(r) {
        build_network();
    }

    void iterate() {
        for (size_t i = 0; i < one_iteration_caculate_count; i++)
            caculate();
        optimize();
    }

    size_t number_of_defection () {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy::DEFECTION)
                sum++;
        }
        return sum;
    }

    size_t number_of_cooperation() {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy::COOPERATION)
                sum++;
        }
        return sum;
    }

    size_t number_of_TFT() {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy::TFT)
                sum++;
        }
        return sum;
    }
    

private:
   void build_network() {
        network = std::make_unique<network_type>(network_size, new_node_edge_count);
        for (auto &node : network->nodes) {
            // 网络初始化为随机策略
            node.data.strategy = gambling::get_rand_strategy();
        }
        // TFT初始化
        for (auto &node : network->nodes) {
            if (node.data.strategy == strategy::TFT) {
                for (auto const &neighbor : node.neighbors) {
                    if (network->nodes[neighbor].data.strategy == strategy::TFT) 
                        node.data.neighbors_impression[neighbor] = gambling::get_rand_behavior();
                    else {
                        node.data.neighbors_impression[neighbor] 
                        = (behavior) network->nodes[neighbor].data.strategy;
                    }
                }
            }
        }

    }

    void caculate() {
        std::vector<double> this_tern_payoff(network->nodes.size(), 0);
        for (auto const &edge : network->edges) {
            ID x = edge.source;
            ID y = edge.target;
            behavior x_behavior;
            behavior y_behavior;
            
            // two TFT
            if (network->nodes[x].data.strategy == strategy::TFT 
            && network->nodes[y].data.strategy == strategy::TFT) {
                x_behavior = network->nodes[x].data.neighbors_impression[y];
                y_behavior = network->nodes[y].data.neighbors_impression[x];
            }
            // no TFT
            else if (network->nodes[x].data.strategy != strategy::TFT 
            && network->nodes[y].data.strategy != strategy::TFT) {
                x_behavior = (behavior) network->nodes[x].data.strategy;
                y_behavior = (behavior) network->nodes[y].data.strategy;
            }
            // one TFT
            else {
                if (network->nodes[x].data.strategy == strategy::TFT) {
                    x_behavior = network->nodes[x].data.neighbors_impression[y];
                    y_behavior = (behavior) network->nodes[y].data.strategy;
                }
                else {
                    x_behavior = (behavior) network->nodes[x].data.strategy;
                    y_behavior = network->nodes[y].data.neighbors_impression[x];
                }
            }

            battle(x_behavior, y_behavior, this_tern_payoff[x], 
            this_tern_payoff[y], r, gambling_type);
        }
        // 更新收益
        for (size_t i = 0; i < this_tern_payoff.size(); i++) {
            network->nodes[i].data.this_tern_payoff = this_tern_payoff[i];
            network->nodes[i].data.payoff += this_tern_payoff[i];
        }
    }

    void optimize() {
        std::vector<int> this_tern_strategy(network->nodes.size(), -1);
        
        for (size_t source_ID = 0; source_ID < network->nodes.size(); source_ID++) {
            double neighbors_p = network->nodes[source_ID].degree() / (double) 1;
            double rand = get_rand_p();
            
            size_t neighbor_index = rand / neighbors_p;
            ID target_ID = network->nodes[source_ID].neighbors[neighbor_index];

            if (network->nodes[source_ID].data.strategy == network->nodes[target_ID].data.strategy)
                continue;

            double p = 1 / (1 + exp((network->nodes[source_ID].data.this_tern_payoff 
            - network->nodes[target_ID].data.this_tern_payoff) / 0.01));
            rand = get_rand_p();

            if (p > rand)
                this_tern_strategy[source_ID] = (int) network->nodes[target_ID].data.strategy;
        }

        // 更新策略
        for (size_t i = 0; i < this_tern_strategy.size(); i++) {
            if (this_tern_strategy[i] == -1)
                continue;
            network->nodes[i].data.strategy = (strategy) this_tern_strategy[i];
        }
        // 本回收益归零
        for (auto &node : network->nodes) 
            node.data.this_tern_payoff = 0;       
    }

};



}


#endif