#include <unordered_map>
#include "BaNetwork.hpp"
#include "GridNetwork.hpp"
#include "GameMethod.hpp"
#include "Strategy.hpp"
#include "RandomGenerator.hpp"

namespace ngl {

template<class StrategyType>
struct NodeDataBase {
    StrategyType strategy = 0;
    double payoff = 0;
};

struct TFTNodeData : public NodeDataBase<TFTStrategy> {
    std::unordered_map<ID, Action> neighborsImpression;
};

struct DefaultNodeData : public NodeDataBase<DefaultStrategy> {};

} /* End of namespace ngl */