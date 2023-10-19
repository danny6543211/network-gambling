#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#include <deque>
#include "rand.h"

typedef size_t ID;

template<class DataType>
struct __node {
    std::vector<ID> neighbors;
    DataType data;

    size_t degrees() {
        return neighbors.size();
    }
};

struct __edge {
    ID source;
    ID target;

    __edge(ID source, ID target) 
    : source(source), target(target) {}
};

template<class DataType>
struct __network__base
{
    typedef __node<DataType>   node;
    typedef __edge             edge;


    std::vector<node> nodes;
    std::vector<edge> edges;

    size_t network_degrees_sum() {
        size_t sum = 0;
        for (auto node : nodes)
            sum += node.neighbors.size();
        return sum;
    }

    void connect(ID x, ID y) {
        nodes[x].neighbors.push_back(y);
        nodes[y].neighbors.push_back(x);
        edges.push_back(edge(x, y));
    }
};


#endif