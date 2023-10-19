#ifndef NETWORK_GAMBLING_H
#define NETWORK_GAMBLING_H

#include <unordered_map>

// 使用无标度网络
#include "./include/scale_free_network.h"

// strategy
enum class strategy {BETRAY, COOPERATE, TFT};
enum class behavior {BETRAY, COOPERATE};
strategy rand_strategy() { 
    return (strategy) (get_rand_int() % 3);
}
behavior rand_behavior() {
    return (behavior) (get_rand_int() % 2);
}

// data type
struct TFT_data_type {
    strategy strategy;
    double payoff = 0;
    double this_tern_payoff = 0;
    std::unordered_map<ID, behavior> neighbors_impression;
};

class network_gambling : network::scale_free_network<TFT_data_type> {

    // initailize all node
    void init() {

    }

    // caculate value
    void caculate() {

    }

    // optimize behavior
    void optimize() {

    }
};


#endif