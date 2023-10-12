#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "node.h"
#include "tools.h"

#define COOPERATE        1
#define BETRAY           0
// 费米传播的系数k
#define K                0.1
// 
#define INIT_NODE_COUNT  5

struct network_factor {   
    double cooperate_payoff = 0;
    double be_betray_payoff = 0;
    double betray_ok_payoff = 0;
    double rationality      = 0;

    network_factor(double cooperate_payoff, double be_betray_payoff
    , double betray_ok_payoff, double rationality) 
    : cooperate_payoff(cooperate_payoff), be_betray_payoff(be_betray_payoff)
    , betray_ok_payoff(betray_ok_payoff), rationality(rationality) {}
};

class network {
public:
    std::vector<std::shared_ptr<node>> nodes;
    network_factor factor;

    network(network_factor init) : factor(init) {
        for (size_t i = 0; i < INIT_NODE_COUNT; i++)
            add_node();
        initial_node_connect();
    }

    void gambling(size_t iterate_count) {
        for (size_t i = 0; i < iterate_count; i++) {
            add_node();
            connect_new_node();
            caculate();
            optimize();
        }
    }

    std::vector<double> get_payoff() {
        std::vector<double> ret;
        for (size_t i = 0; i < nodes.size(); i++) {
            ret.push_back(nodes[i]->payoff);
        }
        return ret;
    }

    std::vector<int> get_strategy() {
        std::vector<int> ret;
        for (size_t i = 0; i < nodes.size(); i++) {
            ret.push_back(nodes[i]->strategy);
        }
        return ret;
    }

    std::vector<size_t> get_degrees() {
        std::vector<size_t> ret;
        for (size_t i = 0; i < nodes.size(); i++) {
            ret.push_back(nodes[i]->neighbors.size());
        }
        return ret;   
    }

    double get_cooperation_density() {
        size_t cooperation_count = 0;
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i]->strategy == COOPERATE)
                cooperation_count++;
        }
        return (double) cooperation_count / nodes.size();
    }




private:
    void add_node() {
        bool strategy = get_random() % 2;
        std::shared_ptr<node> temp = std::make_shared<node>(0, strategy);
        nodes.push_back(temp);
    }

    void connect_new_node() {
        size_t node_count = nodes.size();
        do {
            for (size_t i = 0; i < node_count-1; i++) {
                double rand = (double) (get_random()%degrees_sum()) / degrees_sum();
                double p = (double) nodes[i]->neighbors.size() / degrees_sum();
                if (p > rand) 
                    connect(nodes[node_count-1], nodes[i]);
            }
        } while (nodes[node_count-1]->neighbors.size() == 0);
    }

    void caculate() {
        for (size_t i = 0; i < nodes.size(); i++) {
            for (size_t j = 0; j < nodes[i]->neighbors.size(); j++) {
                if (nodes[i]->neighbors[j]->battle_count == nodes[i]->neighbors[j]->neighbors.size())
                    continue;
                else 
                    battle(nodes[i], nodes[i]->neighbors[j]);
            }
        }
        for (size_t i = 0; i < nodes.size(); i++) {
            nodes[i]->battle_count = 0;
        }
    }

    void optimize() {
        for (size_t i = 0; i < nodes.size(); i++) {
            
        }
    }

    void initial_node_connect() {
        for (size_t i = 0; i < INIT_NODE_COUNT; i++) {
            for (size_t j = i+1; j < INIT_NODE_COUNT; j++) {
                connect(nodes[i], nodes[j]);
            }
        }
    }

    size_t degrees_sum() {
        size_t sum = 0;
        for (size_t i = 0; i < nodes.size(); i++) 
            sum += nodes[i]->neighbors.size();
        return sum;
    }

    void battle(std::shared_ptr<node> x, std::shared_ptr<node> y) {
        x->battle_count++;
        y->battle_count++;
        if (x->strategy == y->strategy) {
            if (x->strategy == COOPERATE) {
                x->payoff += factor.cooperate_payoff;
                y->payoff += factor.cooperate_payoff;
            }
            else {
                x->payoff += factor.be_betray_payoff;
                y->payoff += factor.be_betray_payoff;
            }
        }
        else {
            if (x->strategy == COOPERATE) {
                x->payoff += factor.be_betray_payoff;
                y->payoff += factor.betray_ok_payoff;
            }
            else {
                x->payoff += factor.betray_ok_payoff;
                y->payoff += factor.be_betray_payoff;
            }
        }
    }

};

#endif