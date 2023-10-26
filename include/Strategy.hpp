#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "RandomGenerator.hpp"

namespace ngl {

enum class DefaultStrategy {
    Cooperation, Defection
};

enum class TFTStrategy {
    Cooperation, Defection, TFT
};

enum class Action {
    Cooperate, Defect
};

inline DefaultStrategy getRandomDafaultStrategy() {
    return (DefaultStrategy) (ngl::RandomGenerator::getRandomInt() % 2);
}

inline TFTStrategy getRandomTFTStrategy() {
    return (TFTStrategy) (ngl::RandomGenerator::getRandomInt() % 3);
}


inline Action getRandomAction() {
    return (Action) (ngl::RandomGenerator::getRandomInt() % 2);
}


} /* End of namespace ngl */

#endif