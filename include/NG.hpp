#ifndef NG_HPP
#define NG_HPP

#include <memory>
#include "NetworkBase.hpp"
#include "Network.hpp"

#include "StrategyGroup.hpp"
#include "GameMethod.hpp"

namespace ngl {

template<typename Network, typename StrategyGroup, typename GameMethod>
class NG {
public:
    using NodeDataType = typename StrategyGroup::NodeDataType;

    NG(size_t arg1, size_t arg2) {
        network = getNetworkInstance(Network(), StrategyGroup());
        network->build(arg1, arg2);
        initNode(*network);
    }

    void caculate() {

    }

    void optimize() {

    }

    size_t networkSize() {
        return network->networkSize();
    }

    size_t edgeCount() {
        return network->edgeCount();
    }

    auto& operator[](ID id) {
        return (*network)[id];
    }

    auto operator()(size_t i) {
        return (*network)(i);
    }

private:
    std::unique_ptr<NetworkBase<NodeDataType>> network;
};

}   /* End of namespace ngl */

#endif