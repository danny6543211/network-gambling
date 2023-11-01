#ifndef STRATEGY_GROUP
#define STRATEGY_GROUP

#include <unordered_map>
#include "Action.hpp"

namespace ngl {

using ID = unsigned int;

struct ClassicStrategyGroup {
    using EnumValue = enum class CD {
        Cooperation, Defection
    };     
    using NodeDataType = struct {
        EnumValue strategy;
        double payoff; 
    };
};

struct TFTStrategyGroup {
    using EnumValue = enum class CDTFT {
        Cooperation, Defection, TFT
    };
    using NodeDataType = struct {
        EnumValue strategy;
        double payoff = 0;
        std::unordered_map<ID, Action> neighborsImpression;
    };
};

namespace sg {
    using ngl::ClassicStrategyGroup;
    using ngl::TFTStrategyGroup;
}

ClassicStrategyGroup::EnumValue randomEnumValue(ClassicStrategyGroup) {
    return (ClassicStrategyGroup::EnumValue) (RandomGenerator::randomInt() % 2);
}

TFTStrategyGroup::EnumValue randomEnumValue(TFTStrategyGroup) {
    return (TFTStrategyGroup::EnumValue) (RandomGenerator::randomInt() % 3);
}


}   /* End of namespace ngl */

#endif