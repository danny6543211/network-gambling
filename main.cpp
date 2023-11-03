#include <iostream>
#include "NG.hpp"

using namespace ngl;

int main() {
    NG<nw::Grid,sg::ClassicStrategyGroup,gm::PrisonersDilemma> test(100 ,100, 0.1);

    for (size_t i = 0; i < 100; i++) {
        test.caculate();
        test.optimize();
        // auto action = test.getAction();

        // std::cout << "C: " << action["C"] << " ";
        // std::cout << "D: " << action["D"] << " ";
        // std::cout << "\n";
    }
    
}