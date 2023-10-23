#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "rand.hpp"

namespace strategy {

enum class dafault_strategy_type {
    BETRAY, COOPERATE
};

enum class TFT_strategy_type {
    BETRAY, COOPERATE, TFT
};


inline strategy::dafault_strategy_type get_rand_strategy(strategy::dafault_strategy_type) {
    return (strategy::dafault_strategy_type) (get_rand_int() % 2);
}

inline strategy::TFT_strategy_type get_rand_strategy(strategy::TFT_strategy_type) {
    return (strategy::TFT_strategy_type) (get_rand_int() % 3);
}

};

#endif