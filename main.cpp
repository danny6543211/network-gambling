#include <iostream>
#include <fstream>
#include "network_gambling.hpp"

int main() {
    std::fstream file("cooperate_density.csv", std::ios::out);

    // range of r from 0 to 0.5
    for (double r = 0; r < 0.5; r += 0.1) {
        network_gambling test(r);

        for (size_t iteration_count = 0; iteration_count < 100; iteration_count++) {
            test.iterate();
        }

        file << test.get_Betray_count() << ",";
        file << test.get_Cooperate_count() << "\n";
    }

}