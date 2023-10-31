#pragma once

#include <unordered_map>
#include "RandomGenerator.hpp"
#include "Action.hpp"

namespace ngl {

using ID = unsigned int;

namespace Strategy {

struct ClassicStrategy { 
    using EnumValue = enum class CD {
        Cooperation, Defection
    };
    using NodeDataType = struct {
        EnumValue strategy = EnumValue::Cooperation;
        double payoff = 0;
    };

    static CD getRandomStrategy() {
        return static_cast<CD>(RandomGenerator::randomInt() % 2);
    }
};

struct TFTStrategy {
    using EnumValue = enum class CDTFT {
        Cooperation, Defection, TFT
    };
    using NodeDataType = struct {
        EnumValue strategy = EnumValue::Cooperation;
        double payoff = 0;
        std::unordered_map<ID, Action> neighborsImpression;
    };

    static CDTFT getRandomStrategy() {
        return static_cast<CDTFT>(RandomGenerator::randomInt() % 3);
    }
};

}   /* End of namespace strategy */

}   /* End of namespace ngl */