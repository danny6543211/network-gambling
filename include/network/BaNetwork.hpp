#pragma once 

#include <memory>
#include "NetworkBase.hpp"
#include "RandomGenerator.hpp"
#include "Strategy.hpp"

namespace ngl {

template<class NodeDataType>
struct _BaNetwork : public NetworkBase<NodeDataType> {
    using Node = Node<NodeDataType>;

    _BaNetwork(size_t nodeCount, size_t newNodeEdgeCount) {
        this->addNode();
        this->addNode();
        connect(0, 1);

        for (size_t newNode = 2; newNode < nodeCount; newNode++) {
            this->addNode();
            for (size_t edge = 0; edge < newNodeEdgeCount; edge++) {
                std::vector<double> degreeTable(newNode-1, 0);
                size_t degreesOfNetwork = this->degreesOfNetwork();
                for (size_t i = 0; i < degreeTable.size(); i++) 
                    degreeTable[i] = (*this)[i].degree() / (double) degreesOfNetwork;
                
                double rand = RandomGenerator::randomProbability();
                size_t connectedNode = 0;
                for (auto i : degreeTable) {
                    rand -= i;
                    if (rand < 1e-10)
                        break;
                    connectedNode++;
                }

                connect(newNode, connectedNode);
            }
        }
    }

    
private:
    void connect(ID x, ID y) {
        this->addEdge(x, y);
        (*this)[x].neighbors.push_back(y);
        (*this)[y].neighbors.push_back(x);
    }
};

namespace Network {

    struct BaNetwork {
        static std::unique_ptr<_BaNetwork<Strategy::ClassicStrategy::NodeDataType>> 
        build(size_t arg1, size_t arg2, Strategy::ClassicStrategy) {
            _BaNetwork<Strategy::ClassicStrategy::NodeDataType> temp(arg1, arg2);
            return std::make_unique<_BaNetwork<Strategy::ClassicStrategy::NodeDataType>>
            (temp);
        }

        static std::unique_ptr<_BaNetwork<Strategy::TFTStrategy::NodeDataType>> 
        build(size_t arg1, size_t arg2, Strategy::TFTStrategy) {
            _BaNetwork<Strategy::TFTStrategy::NodeDataType> temp(arg1, arg2);
            return std::make_unique<_BaNetwork<Strategy::TFTStrategy::NodeDataType>>
            (temp);
        }
    };


}   /* End of namespace network */

}   /* End of namespace ngl */