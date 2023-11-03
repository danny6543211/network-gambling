#ifndef NG_HPP
#define NG_HPP

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "NetworkBase.hpp"
#include "NetworkConstruct.hpp"
#include "Caculate.hpp"

#include "StrategyGroup.hpp"
#include "GameMethod.hpp"

namespace ngl {

template<typename Network, typename StrategyGroup, typename GameMethod>
class NG {
public:
    using NodeDataType = typename StrategyGroup::NodeDataType;
    using StrategyEnumValue    = typename StrategyGroup::EnumValue;

    NG(size_t arg1, size_t arg2, double r) : r(r) {
        network = getNetworkInstance(Network(), StrategyGroup());
        network->build(arg1, arg2);
        initNode(*network);
    }

    void caculate() {
        _caculate(*network, thisTernPayoff, thisTernAction, r, GameMethod());
    }

    void optimize() {
        std::vector<int> thisTernStrategy(network->networkSize(), -1);
        
        for (size_t i = 0; i < network->networkSize(); i++) {
            size_t neighborsCount = (*network)[i].neighbors.size();
            size_t select = RandomGenerator::randomInt() % neighborsCount;
            ID neighborID = (*network)[i].neighbors[select];
            
            double p = 1 / (double)
            (exp((thisTernPayoff[i]-thisTernPayoff[neighborID])/0.01) + 1);
            double rand = RandomGenerator::randomProbability();

            if (p > rand) 
                thisTernStrategy[i] = static_cast<int>((*network)[neighborID].data.strategy);
        }

        for (size_t i = 0; i < thisTernStrategy.size(); i++) {
            if (thisTernStrategy[i] == -1)
                continue;
            (*network)[i].data.strategy = static_cast<StrategyEnumValue>(thisTernStrategy[i]);
        }
    }

    std::vector<int> getStrategy() {
        std::vector<int> temp;
        for (size_t i = 0; i < network->networkSize(); i++) {
            temp.push_back((int) (*network)[i].data.strategy);
        }
        return std::move(temp);
    }

    std::vector<double> getPayoff() {
        std::vector<double> temp;
        for (size_t i = 0; i < network->networkSize(); i++) {
            temp.push_back((*network)[i].data.payoff);
        }
        return std::move(temp);
    }

    // Traverse the edges to get 'C, D, CC, CD, DD'
    const std::unordered_map<std::string, size_t>& getAction() {
        return thisTernAction;
    }

    


private:
    double r = 0;
    std::unique_ptr<NetworkBase<NodeDataType>> network;
    std::vector<double> thisTernPayoff;
    std::unordered_map<std::string, size_t> thisTernAction;
    
};

}   /* End of namespace ngl */

#endif