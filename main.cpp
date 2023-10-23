#include <iostream>
#include "network_gambling.hpp"



int main() {
    ng::network_gambling test;

    for (int i = 0; i < 10000; i++) {
        test.iterate();
    }

    std::cout << test.number_of_cooperation() << " ";
    std::cout << test.number_of_defection() << " ";
    std::cout << test.number_of_TFT() << " ";


}