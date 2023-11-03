#ifndef CACULATE_HPP
#define CACULATE_HPP

#include <vector>
#include <unordered_map>

#include "NetworkBase.hpp"
#include "StrategyGroup.hpp"
#include "Action.hpp"

namespace ngl {

template<typename GameMethod>
void _caculate(NetworkBase<ClassicStrategyGroup::NodeDataType>& network, 
    std::vector<double>& thisTernpayoff, 
    std::unordered_map<std::string, size_t>& thisTernAction,
    double r, GameMethod) {

    thisTernAction["C"] = 0;
    thisTernAction["D"] = 0;
    thisTernAction["CC"] = 0;
    thisTernAction["CD"] = 0;
    thisTernAction["DD"] = 0;
    std::vector<double> payoff(network.networkSize(), 0);
    
    for (size_t i = 0; i < network.edgeCount(); i++) {
        ID x = network(i).source;
        ID y = network(i).target;
        Action xAction = static_cast<Action>(network[x].data.strategy);
        Action yAction = static_cast<Action>(network[y].data.strategy);

        GameMethod::battle(xAction, yAction, payoff[x], payoff[y], r);

        if (xAction == yAction) {
            if (xAction == Action::Cooperate) {
                thisTernAction["C"] += 2;
                
                thisTernAction["CC"]++;
            }
            else {
                thisTernAction["D"] += 2;
                
                thisTernAction["DD"]++;
            }
        }
        else {
            thisTernAction["C"]++;
            thisTernAction["D"]++;

            thisTernAction["CD"]++;
        }
    }
    
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.payoff += payoff[i];
    }
    thisTernpayoff = payoff;
}

template<typename GameMethod>
void _caculate(
    NetworkBase<TFTStrategyGroup::NodeDataType>& network, 
    std::vector<double>& thisTernPayoff, 
    std::unordered_map<std::string, size_t>& thisTernAction,
    double r, GameMethod) {

    thisTernAction["C"] = 0;
    thisTernAction["D"] = 0;
    thisTernAction["CC"] = 0;
    thisTernAction["CD"] = 0;
    thisTernAction["DD"] = 0;
    std::vector<double> payoff(network.networkSize(), 0);

    for (size_t i = 0; i < network.edgeCount(); i++) {
        using StrategyEnumValue = TFTStrategyGroup::EnumValue;

        ID x = network(i).source;
        ID y = network(i).target;
        StrategyEnumValue xStrategy = network[x].data.strategy;
        StrategyEnumValue yStrategy = network[y].data.strategy;
        
        Action xAction;
        Action yAction;

        // find the action of TFT node
        // all TFT
        if (xStrategy == StrategyEnumValue::TFT && yStrategy == StrategyEnumValue::TFT) {
            xAction = network[x].data.neighborsImpression[y];
            yAction = network[y].data.neighborsImpression[x];
        }
        // one TFT
        else if (xStrategy == StrategyEnumValue::TFT || yStrategy == StrategyEnumValue::TFT) {
            if (xStrategy == StrategyEnumValue::TFT) {
                xAction = network[x].data.neighborsImpression[y];
                yAction = static_cast<Action>(network[y].data.strategy);
            }
            else {
                xAction = static_cast<Action>(network[x].data.strategy);
                yAction = network[y].data.neighborsImpression[x];
            }
        }
        // no TFT
        else {
            xAction = static_cast<Action>(network[x].data.strategy);
            yAction = static_cast<Action>(network[y].data.strategy);
        }

        GameMethod::battle(xAction, yAction, payoff[x], payoff[y], r);

        if (xAction == yAction) {
            if (xAction == Action::Cooperate) {
                thisTernAction["C"] += 2;
                
                thisTernAction["CC"]++;
            }
            else {
                thisTernAction["D"] += 2;
                
                thisTernAction["DD"]++;
            }
        }
        else {
            thisTernAction["C"]++;
            thisTernAction["D"]++;

            thisTernAction["CD"]++;
        }
    }
    
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.payoff += payoff[i];
    }
    thisTernPayoff = std::move(payoff);
}


}   /* End of namespace ngl */

#endif