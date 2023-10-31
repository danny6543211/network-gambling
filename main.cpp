#include <iostream>
#include <memory>

#include "NG.hpp"

using namespace ngl;

int main() {
    NG<Network::GridNetwork, Strategy::TFTStrategy, GameMethod::PrisonersDilemma>
    test(10, 10);
    
    std::cout << test.networkSize() << "\n";
}