#ifndef NETWORK
#define NETWORK

#include <memory>
#include "BaNetwork.hpp"
#include "GridNetwork.hpp"

#include "NetworkBase.hpp"
#include "StrategyGroup.hpp"

namespace ngl {

using namespace nw; 

template<typename StrategyGroup>
auto getNetworkInstance(BA, StrategyGroup) {
    using NodeDataType = typename StrategyGroup::NodeDataType;
    return std::make_unique<BaNetwork<NodeDataType>>(BaNetwork<NodeDataType>());
}

template<typename StrategyGroup>
auto getNetworkInstance(Grid, StrategyGroup) {
    using NodeDataType = typename StrategyGroup::NodeDataType;
    return std::make_unique<GridNetwork<NodeDataType>>(GridNetwork<NodeDataType>());
}

void initNode(NetworkBase<TFTStrategyGroup::NodeDataType>& network) {
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.strategy = randomEnumValue(TFTStrategyGroup());
    }
    // initialize impression to neighbors
    for (size_t currentID = 0; currentID < network.networkSize(); currentID++) {
        if (network[currentID].data.strategy != TFTStrategyGroup::EnumValue::TFT)
            continue;
        for (size_t i = 0; i < network[currentID].neighbors.size(); i++) {
            ID neighborID = network[currentID].neighbors[i];
            if (network[neighborID].data.strategy == TFTStrategyGroup::EnumValue::TFT) {
                network[currentID].data.neighborsImpression[neighborID] = randomAction();
            }
            else {
                network[currentID].data.neighborsImpression[neighborID] 
                = static_cast<Action>(network[neighborID].data.strategy);
            }
        }
    }  
}

void initNode(NetworkBase<ClassicStrategyGroup::NodeDataType>& network) {
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.strategy = randomEnumValue(ClassicStrategyGroup());
    }    
}



}

#endif