#ifndef CACULATE_HPP
#define CACULATE_HPP

#include <vector>

#include "NetworkBase.hpp"
#include "StrategyGroup.hpp"
#include "Action.hpp"

namespace ngl {

template<typename GameMethod>
void _caculate(NetworkBase<ClassicStrategyGroup::NodeDataType>& network, 
    std::vector<double>& this_tern_payoff, double r, GameMethod) {
    std::vector<double> payoff(network.networkSize(), 0);
    for (size_t i = 0; i < network.edgeCount(); i++) {
        ID x = network(i).source;
        ID y = network(i).target;
        Action xAction = static_cast<Action>(network[x].data.strategy);
        Action yAction = static_cast<Action>(network[y].data.strategy);

        GameMethod::battle(xAction, yAction, payoff[x], payoff[y], r);
    }
    
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.payoff += payoff[i];
    }
    this_tern_payoff = std::move(payoff);
}

template<typename GameMethod>
void _caculate(NetworkBase<TFTStrategyGroup::NodeDataType>& network, 
    std::vector<double>& this_tern_payoff, double r, GameMethod) {
    std::vector<double> payoff(network.networkSize(), 0);
    for (size_t i = 0; i < network.edgeCount(); i++) {
        ID x = network(i).source;
        ID y = network(i).target;
        
        // find the action of TFT node...................


        // GameMethod::battle(xAction, yAction, payoff[x], payoff[y], r);
    }
    
    for (size_t i = 0; i < network.networkSize(); i++) {
        network[i].data.payoff += payoff[i];
    }
    this_tern_payoff = std::move(payoff);
}


}   /* End of namespace ngl */

#endif