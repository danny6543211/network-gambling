#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "scale_free_network.h"


int main() {
    scale_free_network x(5);
    x.export_node_status("./data/network_init_status.csv");

    x.caculate(1, 0.5);
    x.export_node_status("./data/network_end_status.csv");
}