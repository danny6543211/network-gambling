#include <iostream>
#include "network.h"

int main() {
    network_factor factor(1, 0, 1.2, 0.5);
    network x(factor);
    
    x.gambling(100);

    auto payoffs  = x.get_payoff();
    auto strategy = x.get_strategy();
    auto degrees  = x.get_degrees();
    double cooperation_density = x.get_cooperation_density();

    std::cout << "payoff:" << std::endl;
    for (auto i : payoffs) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "strategy:" << std::endl;
    for (auto i : strategy) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "degrees:" << std::endl;
    for (auto i : degrees) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "cooperation_density: " << cooperation_density << std::endl;

}