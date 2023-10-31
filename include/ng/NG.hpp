#pragma once 

#include <memory>
#include "NetworkBase.hpp"
#include "BaNetwork.hpp"
#include "GridNetwork.hpp"
#include "GameMethod.hpp"

namespace ngl {

template<class Network, class Strategy, class GameMethod>
struct NG {
    NG(size_t arg1, size_t arg2) {
        network = Network::build(arg1, arg2, Strategy());
    }    



public:
    auto operator[](ID id) {
        return (*network)[id];
    }

    auto operator()(size_t i) {
        return (*network)(i);
    }

    size_t networkSize() {
        return (*network).networkSize();
    }

    size_t edgeCount() {
        return (*network).edgeCount();
    }

private:
    std::unique_ptr<NetworkBase<typename Strategy::NodeDataType>> network;
};

}   /* End of namespace ngl */