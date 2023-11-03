#ifndef ACTION
#define ACTION

#include "RandomGenerator.hpp"

namespace ngl {

enum class Action {
    Defect, Cooperate
};

Action randomAction() {
    return (Action) (RandomGenerator::randomInt() % 2);
}

}   /* End of namespace ngl */

#endif