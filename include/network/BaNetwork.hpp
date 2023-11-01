#ifndef BA_NETWORK
#define BA_NETWORK

#include <memory>
#include "NetworkBase.hpp"
#include "RandomGenerator.hpp"

namespace ngl {

template<typename NodeDataType>
struct BaNetwork : public NetworkBase<NodeDataType> {

    BaNetwork() {}

    void build(size_t nodeCount, size_t newNodeEdgeCount) {
        this->addNode();
        this->addNode();
        connect(0, 1);

        for (ID newNodeID = 2; newNodeID < nodeCount; newNodeID++) {
            this->addNode();
            for (size_t edgeCount = 0; edgeCount < newNodeEdgeCount; edgeCount++) {
                std::vector<double> degreeTable(newNodeID-1, 0);
                size_t degrees = this->degreesOfNetwork();
                for (size_t i = 0; i < degreeTable.size(); i++) 
                    degreeTable[i] = (*this)[i].degree() / (double) degrees;
                
                double rand = RandomGenerator::randomProbability();
                size_t connectedNodeID = 0;
                for (auto i : degreeTable) {
                    rand -= i;
                    if (rand < 1e-10)
                        break;
                    connectedNodeID++;
                }

                connect(newNodeID, connectedNodeID);    
            }
        }
        this->ShrinkToFit();
    }

private:
    void connect(ID x, ID y) {
        this->addEdge(x, y);
        (*this)[x].neighbors.push_back(y);
        (*this)[y].neighbors.push_back(x);
    }
};

namespace nw {

struct BA {};

}


}   /* End of namespace ngl */

#endif