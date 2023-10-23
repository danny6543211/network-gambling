#include <unordered_map>
#include <memory>

#include "BA_network.hpp"
#include "strategy.hpp"
#include "behavior.hpp"
#include "gaming_method.hpp"
#include "rand.hpp"


struct node_data {
    using ID            = unsigned int;
    using strategy_type = strategy::TFT_strategy_type;

    strategy_type strategy = strategy_type::COOPERATE;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::unordered_map<ID, behavior> neighbors_impression;
};

class network_gambling {
public:
    using ID                  = unsigned int;
    using strategy_type       = strategy::TFT_strategy_type;
    using network_type        = network::BA_network<node_data>;
    using gaming_method_type  = gaming_method::prisoners_dilemma;
    
    std::unique_ptr<network_type> network;
    
private:

    size_t network_size                 = 100;
    size_t new_node_edge_count          = 1;
    size_t one_iteration_caculate_count = 5;
    double r = 0; 

public:
    network_gambling() {
        build_network();
    }

    network_gambling(double r) : r(r) {
        build_network();
    }

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

    void set_r(double r) {
        this->r = r;
    }

    void rebuild() {
        network = nullptr;
        build_network();
    }

    size_t get_Betray_count() {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy_type::BETRAY)
                sum++;
        }
        return sum;
    }

    size_t get_Cooperate_count() {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy_type::COOPERATE)
                sum++;
        }
        return sum;
    }

private:
    void build_network() {
        network = std::make_unique<network_type>(network_size, new_node_edge_count);
        for (auto &node : network->nodes) {
            // 网络初始化为对自己随机策略，对邻居随机印象
            node.data.strategy = get_rand_strategy(strategy_type());
            for (auto &neighbor : node.neighbors) 
                node.data.neighbors_impression[neighbor] = get_rand_behavior();
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
            if (network->nodes[x].data.strategy == strategy_type::TFT 
            && network->nodes[y].data.strategy == strategy_type::TFT) {
                x_behavior = network->nodes[x].data.neighbors_impression[y];
                y_behavior = network->nodes[y].data.neighbors_impression[x];
            }
            // no TFT
            else if (network->nodes[x].data.strategy != strategy_type::TFT 
            && network->nodes[y].data.strategy != strategy_type::TFT) {
                x_behavior = (behavior) network->nodes[x].data.strategy;
                y_behavior = (behavior) network->nodes[y].data.strategy;
            }
            // one TFT
            else {
                if (network->nodes[x].data.strategy == strategy_type::TFT) {
                    x_behavior = network->nodes[x].data.neighbors_impression[y];
                    y_behavior = (behavior) network->nodes[y].data.strategy;
                }
                else {
                    x_behavior = (behavior) network->nodes[x].data.strategy;
                    y_behavior = network->nodes[y].data.neighbors_impression[x];
                }
            }

            battle(x_behavior, y_behavior, this_tern_payoff[x], 
            this_tern_payoff[y], r, gaming_method_type());
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
            std::vector<double> degrees_table;
            size_t neighbors_degrees_sum = 0;
            for (auto neighbor_ID : network->nodes[source_ID].neighbors) {
                size_t neighbor_degrees = network->nodes[neighbor_ID].degree();
                degrees_table.push_back(neighbor_degrees);
                neighbors_degrees_sum += neighbor_degrees;
            }
            // 把 度/邻居所有度 转换为概率
            for (auto &i : degrees_table)
                i /= (double) neighbors_degrees_sum;

            double rand = get_rand_p();
            size_t target_neighbor_index = 0;
            for (auto degrees_p : degrees_table) {
                rand -= degrees_p;
                if (rand < 1e-6)
                    break;
                target_neighbor_index++;
            }
            ID target_ID = network->nodes[source_ID].neighbors[target_neighbor_index];

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
            network->nodes[i].data.strategy = (strategy_type) this_tern_strategy[i];
        }
        // 本回收益归零
        for (auto &node : network->nodes) 
            node.data.this_tern_payoff = 0;       
    }
    
};