#ifndef NETWORK_H
#define NETWORK_H

#include <deque>
#include "node.h"
#include "rand.h"

struct __edge {
    unsigned int source;
    unsigned int target;

    __edge(unsigned int source, unsigned int target) 
    : source(source), target(target) {}

    bool has(unsigned int x) {
        if (source == x || target == x)
            return true;
        return false;
    }
};

template<class DataType>
struct __network__base
{
    typedef __node<DataType> node;

    std::deque<__node<DataType>> nodes;
    std::vector<__edge> edges;

    size_t degrees_sum() {
        size_t sum = 0;
        for (auto node : nodes)
            sum += node.neighbors.size();
        return sum;
    }

    void connect(size_t i, size_t j) {
        nodes[i].connect(&nodes[j]);
        edges.push_back(__edge(i, j));
    }
};


#endif