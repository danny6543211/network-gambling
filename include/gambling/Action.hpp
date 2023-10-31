#pragma once 

#include "RandomGenerator.hpp"

namespace ngl {

enum class Action {
    Cooperate, Defect
};

Action randomAction() {
    return (Action) (RandomGenerator::randomInt() % 2);
}

}   /* End of namespace ngl */