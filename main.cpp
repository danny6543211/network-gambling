#include <iostream>
#include "NG.hpp"

using namespace ngl;

int main() {
    NG<nw::Grid,sg::TFTStrategyGroup,gm::PrisonersDilemma> test(10 ,10);

    for (size_t i = 0; i < test.networkSize(); i++) {
        std::cout << (int) test[i].data.strategy << " ";
    }
}