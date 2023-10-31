#define FMT_HEADER_ONLY
#include <iostream>
#include <memory>

#include "fmt/core.h"
#include "NG.hpp"

using namespace ngl;

int main() {
    NG<Network::GridNetwork, Strategy::TFTStrategy, GameMethod::PrisonersDilemma>
    test(10, 10);
    
    fmt::print("{}", test.networkSize());
}