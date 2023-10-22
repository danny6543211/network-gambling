#include <unordered_map>
#include <memory>
#include "rand.h"
#include "BA_network.hpp"

enum class strategy {BETRAY, COOPERATE, TFT};
enum class behavior {BETRAY, COOPERATE};
enum class game {snowdrift_game, prisoners_dilemma};
strategy rand_strategy() { return (strategy) (get_rand_int() % 3); }
behavior rand_behavior() { return (behavior) (get_rand_int() % 2); }

struct node_data {
    strategy strategy = strategy::COOPERATE;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::unordered_map<ID, behavior> neighbors_impression;
};

class gambling {
public:
    typedef __scale_free_network<node_data> scale_free_network;

    std::unique_ptr<scale_free_network> network;
private:
    game game_type = game::snowdrift_game;
    size_t network_size = 100;
    size_t new_node_edge_count = 1;
    size_t one_iteration_caculate_count = 5;
    double r = 0;

public:
    gambling() {}

    void set_r(double r) { this->r = r; }
    void reset() { network = nullptr; }

    void iterate() {
        if (network == nullptr)
            build();
        for (size_t i = 0; i < one_iteration_caculate_count; i++)
            caculate();
        optimize();
    }

    double payoff() {
        double sum = 0;
        for (auto &node : network->nodes)
            sum += node.data.payoff;
        return sum;
    }

    size_t C_count() {
        size_t sum = 0;
        for (auto &node : network->nodes) {
            if (node.data.strategy == strategy::COOPERATE)
                sum++;
        }
        return sum;
    }

    size_t B_count() {
        size_t sum = 0;
        for (auto &node : network->nodes) {
            if (node.data.strategy == strategy::BETRAY)
                sum++;
        }
        return sum;
    }

    size_t T_count() {
        size_t sum = 0;
        for (auto const &node : network->nodes) {
            if (node.data.strategy == strategy::TFT)
                sum++;
        }
        return sum;
    }

private:
    void build() {
        network = nullptr;
        network = std::make_unique<scale_free_network>(network_size, new_node_edge_count);
        for (auto &node : network->nodes) {
            // 网络初始化为对自己随机策略，对邻居随机印象
            node.data.strategy = rand_strategy();
            for (size_t j = 0; j < node.neighbors.size(); j++) {
                node.data.neighbors_impression[node.neighbors[j]] = rand_behavior();
            }
        }
    }

    void caculate() {
        std::vector<double> this_tern_payoff(network->nodes.size(), 0);
        for (auto edge : network->edges) {
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

            if (game_type == game::snowdrift_game)
                snowdrift_battle(x, x_behavior, y, y_behavior, this_tern_payoff, r);
            else if (game_type == game::prisoners_dilemma)
                prisoners_battle(x, x_behavior, y, y_behavior, this_tern_payoff, r);            
        }
    
        // 更新收益
        for (size_t i = 0; i < this_tern_payoff.size(); i++) {
            network->nodes[i].data.this_tern_payoff = this_tern_payoff[i];
            network->nodes[i].data.payoff += network->nodes[i].data.this_tern_payoff;
        }
    }

    void optimize() {
        std::vector<int> this_tern_strategy(network->nodes.size(), -1);
        
        for (size_t source_ID = 0; source_ID < network->nodes.size(); source_ID++) {
            std::vector<double> degrees_table;
            size_t neighbors_degrees_sum = 0;
            for (auto neighbor_ID : network->nodes[source_ID].neighbors) {
                size_t neighbor_degrees = network->nodes[neighbor_ID].degrees();
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
            ID target_ID = network->nodes[source_ID].neighbors[target_neighbor_index];

            if (network->nodes[source_ID].data.strategy == network->nodes[target_ID].data.strategy)
                continue;

            double p = 1 / (1 + exp((network->nodes[source_ID].data.this_tern_payoff 
            - network->nodes[target_ID].data.this_tern_payoff) / 0.01));
            rand = get_rand();

            if (p > rand)
                this_tern_strategy[source_ID] = (int) network->nodes[target_ID].data.strategy;
        }

        // 更新策略
        for (size_t i = 0; i < this_tern_strategy.size(); i++) {
            if (this_tern_strategy[i] == -1)
                continue;
            network->nodes[i].data.strategy = (strategy) this_tern_strategy[i];
        }
    }

    void battle(ID x, behavior x_behavior, ID y, behavior y_behavior, 
    std::vector<double>& payoff, double r, game gambling_method) {

    }

    void snowdrift_battle(ID x, behavior x_behavior, ID y, behavior y_behavior, 
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

    void prisoners_battle(ID x, behavior x_behavior, ID y, behavior y_behavior, 
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
                payoff[y] += 1 + r;
            }
            // x: BETRAY   y: COOPERATE
            else {
                payoff[x] += 1 + r;
            }
        }
    }

    
};
