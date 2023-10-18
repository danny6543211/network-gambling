#include <iostream>
#include <fstream>
#include "scale_free_network.h"


int main() {

    std::ofstream file("data.csv", std::ios::out);

    scale_free_network x(200);
    
    for (auto i : x.nodes)
        file << i.degrees() << "\n";

}