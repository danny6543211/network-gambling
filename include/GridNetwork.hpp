#ifndef GRID_NETWORK_HPP
#define GRID_NETWORK_HPP

namespace ngl {

#include "NetworkBase.hpp"

template<class NodeDataType>
class GridNetwork : public ngl::NetworkBase<ngl::GridNode<NodeDataType>> {
public:
    using NetworkBase = ngl::NetworkBase<ngl::GridNode<NodeDataType>>;
    using Edge        = typename NetworkBase::Edge;
    using Node        = typename NetworkBase::Node;

    GridNetwork(size_t rows, size_t cols) : rows(rows), cols(cols) {
        if (rows < 2 || cols < 2)
            throw "Can not build network with rows or cols below 2";
        // Initialize ID
        for (size_t i = 0; i < rows*cols; i++)
            this->addNode();
        this->nodes.shrink_to_fit();
        // Initialize edges
        for (size_t id = 0; id < this->nodes.size(); id++) {
            // right side
            if ((id+1)%cols == 0)
                this->addEdge(id, id-(cols-1));
            else 
                this->addEdge(id, id+1);
            
            // botton
            if (id >= (rows-1)*cols)
                this->addEdge(id, id-((rows-1)*cols));
            else
                this->addEdge(id, id+cols);
        }
        
    }

private:
    size_t rows;
    size_t cols;
};


} /* End of namespace ng */

namespace network {
    using ngl::GridNetwork;
}

#endif