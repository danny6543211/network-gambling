#ifndef RECORD_H
#define RECORD_H

#include <map>
#include <string>
#include <fstream>
#include "scale_free_network.h"

struct recorder {
    scale_free_network* network;
    std::map<std::string, std::fstream> files_map;

    recorder(scale_free_network& x) { network = &x; }

/*
    recording strategy density
*/
    void recording_density_init(std::string file_path) {
        files_map["density"].open(file_path, std::ios::out);
        files_map["density"] << "Betray,Cooperate,TFT\n";
    }

    void recording_current_density() {
        files_map["density"] << get_strategy_count(strategy::BETRAY) << ",";    
        files_map["density"] << get_strategy_count(strategy::COOPERATE) << ",";    
        files_map["density"] << get_strategy_count(strategy::TFT) << "\n";    
    }

    void recording_density_end() {
        files_map["density"] << "\r\n";
        files_map["density"].close();
    }
/*
    recording all node status
*/
    void recording_all_node_status(std::string file_path) {
        files_map["all_node_status"].open(file_path, std::ios::out);
        files_map["all_node_status"] << "degrees,strategy,payoff" << "\n";

        for (auto node : network->nodes) {
            files_map["all_node_status"] << node.degrees() << ",";
            files_map["all_node_status"] << (int) node.data.strategy << ",";
            files_map["all_node_status"] << node.data.payoff << "\n";
        } 

        files_map["all_node_status"].close();
    }

private:
    size_t get_strategy_count(strategy strategy) {
        size_t sum = 0;
        for (auto node : network->nodes) {
            if (node.data.strategy == strategy)
                sum++;
        }
    return sum;
}
};








#endif