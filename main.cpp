#include <iostream>
#include <memory>

#include "ng.hpp"

using namespace ngl;

int main() {
    NG<Network::GridNetwork, Strategy::TFTStrategy, GameMethod::PrisonersDilemma>
    a(10, 10);
    
    std::cout << a.networkSize() << "\n";
}