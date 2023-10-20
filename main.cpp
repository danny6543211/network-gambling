#include <iostream>
#include <fstream>

#include "gambling.h"

int main() {
    std::fstream file("data.csv", std::ios::out);

    gambling x;

    for (double r = 0; r <= 1; r += 0.1) {
        x.reset();
        x.set_r(r);
        for (size_t i = 0; i < 1000; i++) {
            x.iterate();
        }
        file << x.B_count() << ",";
        file << x.C_count() << ",";
        file << x.T_count() << "\n";
    }

    file << "\r\n";
    file.close();
}