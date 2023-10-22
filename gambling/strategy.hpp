#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "rand.hpp"

enum class strategy {
    BETRAY, COOPERATE, TFT
};

inline strategy get_rand_strategy() {
    return (strategy) (get_rand_int() % 3);
}

#endif