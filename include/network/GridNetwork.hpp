#pragma once 

#include "NetworkBase.hpp"

namespace ngl {

template<class NodeDataType>
struct _GridNetwork : public NetworkBase<NodeDataType>  {
    using Node = Node<NodeDataType>;

    _GridNetwork(size_t rows, size_t cols) : rows(rows), cols(cols) {
       if (rows < 2 || cols < 2)
            throw "Can not build network with rows or cols below 2";
        for (size_t i = 0; i < rows*cols; i++)
            this->addNode();
        this->nodes.shrink_to_fit();
        // Initialize edges
        for (size_t id = 0; id < this->nodes.size(); id++) {
            // right side
            if ((id+1)%cols == 0)
                connect(id, id-(cols-1));
                // this->addEdge(id, id-(cols-1));
            else 
                connect(id, id+1);
                // this->addEdge(id, id+1);
            
            // botton
            if (id >= (rows-1)*cols)
                connect(id, id-((rows-1)*cols));
                // this->addEdge(id, id-((rows-1)*cols));
            else
                connect(id, id+cols);
                // this->addEdge(id, id+cols);
        }    
    }

private:
    size_t rows;
    size_t cols;

    void connect(ID x, ID y) {
        this->addEdge(x, y);
        (*this)[x].neighbors.push_back(y);
        (*this)[y].neighbors.push_back(x);
    }
};

namespace Network {

    struct GridNetwork {
        static std::unique_ptr<_GridNetwork<Strategy::ClassicStrategy::NodeDataType>> 
        build(size_t arg1, size_t arg2, Strategy::ClassicStrategy) {
            _GridNetwork<Strategy::ClassicStrategy::NodeDataType> temp(arg1, arg2);
            return std::make_unique<_GridNetwork<Strategy::ClassicStrategy::NodeDataType>>
            (temp);
        }

        static std::unique_ptr<_GridNetwork<Strategy::TFTStrategy::NodeDataType>> 
        build(size_t arg1, size_t arg2, Strategy::TFTStrategy) {
            _GridNetwork<Strategy::TFTStrategy::NodeDataType> temp(arg1, arg2);
            return std::make_unique<_GridNetwork<Strategy::TFTStrategy::NodeDataType>>
            (temp);
        }
    };


}   /* End of namespace network */

}   /* End of namespace ngl */