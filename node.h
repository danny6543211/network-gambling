#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

struct node {
    double payoff = 0;
    bool strategy = 0;
    size_t battle_count = 0;
    std::vector<std::shared_ptr<node>> neighbors;

    node() {}
    node(double payoff, bool strategy) : payoff(payoff), strategy(strategy) {}
    ~node() {}

    node& operator->() { return *this; }
};

void connect(std::shared_ptr<node> x,std::shared_ptr<node> y) {
    x->neighbors.push_back(y);
    y->neighbors.push_back(x);
}

#endif