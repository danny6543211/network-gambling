#ifndef NETWORK_H
#define NETWORK_H

#include <deque>
#include "node.h"
#include "rand.h"

/*
    Data type of the TFT model
    
    TFT           : TFT strategy's switch          *when the boolean value is true, it represents 'on'.
    payoff        : Aggregate revenue
    strategy      : The node's strategy            *when TFT turn off it used strategy[0]
    prev_strategy : The node's previous strategy   *when TFT turn on it used all vecter
*/
struct TFT_data {
    bool TFT = 0;
    double payoff = 0;
    std::vector<int> strategy;
    std::vector<int> prev_strategy;
};

typedef __node<TFT_data> node;

struct edge {
    unsigned int source;
    unsigned int target;

    edge(unsigned int source, unsigned int target) 
    : source(source), target(target) {}

    bool has(unsigned int x) {
        if (source == x || target == x)
            return true;
        return false;
    }
};

struct __network__base
{
    std::deque<node> nodes;
    std::vector<edge> edges;

    size_t degrees_sum() {
        size_t sum = 0;
        for (auto node : nodes)
            sum += node.neighbors.size();
        return sum;
    }

    void connect(size_t i, size_t j) {
        nodes[i].connect(&nodes[j]);
        edges.push_back(edge(i, j));
    }
};

struct  scale_free_network : public __network__base {

    // 默认新结点连一条边
    size_t new_node_edges_count = 1;

    scale_free_network(size_t node_count) {          
        nodes.push_back(node());
        nodes.push_back(node());
        connect(0, 1);
        for (size_t i = nodes.size(); i < node_count; i++) {
            nodes.push_back(node());
            std::vector<size_t> connect_who;
            for (size_t j = 0; j < new_node_edges_count; j++) {

            }
        }
    }


};

#endif