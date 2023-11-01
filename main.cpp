#include <iostream>
#include "NG.hpp"

using namespace ngl;

int main() {
    NG<nw::Grid,sg::ClassicStrategyGroup,gm::PrisonersDilemma> test(3 ,3);

    for (size_t i = 0; i < 10; i++) {
        test.caculate();
        for (size_t i = 0; i < test.networkSize(); i++) {
            std::cout << (int) test.this_tern_payoff[i] << " ";
        }
        std::cout << "\n";
    }

}