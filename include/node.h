#ifndef NODE_H
#define NODE_H

#include <vector>

/*
    Template of network's node
*/
template<class DataType>
struct __node {
    std::vector<__node*> neighbors;
    DataType data;

    void connect(__node* x) {
        neighbors.push_back(x);
        x->neighbors.push_back(this);
    } 
    
    size_t degrees() {
        return neighbors.size();
    }
};

#endif