#ifndef GRID_NETWORK
#define GRID_NETWORK

#include "NetworkBase.hpp"

namespace ngl {

template<typename NodeDataType>
struct GridNetwork : public NetworkBase<NodeDataType> {
    GridNetwork() {}

    void build(size_t rows, size_t cols) {
        if (rows < 2 || cols < 2)
            throw "Can not build network with rows or cols below 2";
        this->rows = rows;
        this->cols = cols;
        
        for (size_t i = 0; i < rows*cols; i++)
            this->addNode();

        // Initialize edges
        for (size_t id = 0; id < this->networkSize(); id++) {
            // right side
            if ((id+1)%cols == 0)
                connect(id, id-(cols-1));
            else 
                connect(id, id+1);
            
            // botton
            if (id >= (rows-1)*cols)
                connect(id, id-((rows-1)*cols));
            else
                connect(id, id+cols);
        }          
        this->ShrinkToFit();
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

namespace nw {

struct Grid {};

}
    
}   /* End of  namespace ngl */

#endif