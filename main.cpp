#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "./include/scale_free_network.h"

int main() {

    scale_free_network x(100);
    x.export_node_status("./data/network_init_status.csv");
    
    for (size_t i = 0; i < 500; i++) {
        x.caculate(5, 0.5);
        x.opitimize();
    }

    x.export_node_status("./data/network_end_status.csv");
}