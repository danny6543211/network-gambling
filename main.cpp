#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "./include/scale_free_network.h"
#include "./include/record.h"

int main() {
    const unsigned int iteration_count = 100;
    const unsigned int one_iteration_caculate_count = 2;

    scale_free_network x(200);
    recorder x_recorder(x);

    // init status
    x_recorder.recording_all_node_status("./data/init_status.csv");
    
    // strategy density
    x_recorder.recording_density_init("./data/strategy_density.csv");
    for (double r = 0; r < 3; r += 0.01) {
        for (size_t i = 0; i < 1; i++) {
            x.caculate(one_iteration_caculate_count, r);
            x.opitimize();
            // this point density
            x_recorder.recording_current_density();   
        }
    } 
    x_recorder.recording_density_end();

    // end status
    x_recorder.recording_all_node_status("./data/end_status.csv");


}