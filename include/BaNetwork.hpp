#ifndef BA_NETWORK_HPP
#define BA_NETWORK_HPP

#include <vector>
#include "NetworkBase.hpp"
#include "RandomGenerator.hpp"

namespace ngl {

template<class _NodeDataType>
class BaNetwork : public ngl::NetworkBase<ngl::RandomNode<_NodeDataType>> {
public:
    using NodeType = typename ngl::NetworkBase<ngl::RandomNode<_NodeDataType>>::NodeType;
    

    BaNetwork(size_t nodeCount, size_t newNodeEdgeCount) {
        this->addNode();
        this->addNode();
        connect(0, 1);

        for (size_t newNode = 2; newNode < nodeCount; newNode++) {
            this->addNode();
            for (size_t edge = 0; edge < newNodeEdgeCount; edge++) {
                std::vector<double> degreeTable(newNode-1, 0);
                size_t degreesOfNetwork = this->degreesOfNetwork();
                for (size_t i = 0; i < degreeTable.size(); i++) 
                    degreeTable[i] = this->nodes[i].degree() / (double) degreesOfNetwork;
                
                double rand = ngl::RandomGenerator::getRandomDouble();
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
        this->nodes[x].neighbors.push_back(y);
        this->nodes[y].neighbors.push_back(x);
    }
};


} /* End of namespace NG */

namespace network {
    using ngl::BaNetwork;
}

#endif