#include <iostream>
#include <vector>
#include <fstream>
#include "network_gambling.hpp"

int main() {
    ng::network_gambling test;

    std::vector<int> C_behavior;
    std::vector<int> D_behavior;
    std::vector<int> CC_battle;
    std::vector<int> CD_battle;
    std::vector<int> DD_battle;
    std::vector<int> C_strategy;
    std::vector<int> D_strategy;
    std::vector<int> TFT_strategy;

    for (int i = 0; i < 100; i++) {
        // init
        C_strategy.push_back(test.number_of_C_strategy());
        D_strategy.push_back(test.number_of_D_strategy());
        TFT_strategy.push_back(test.number_of_TFT_strategy());

        for (int j = 0; j < 1; j++) {
            test.caculate();
            C_behavior.push_back(test.number_of_C_behavior());
            D_behavior.push_back(test.number_of_D_behavior());
            CC_battle.push_back(test.number_of_CC_battle());
            CD_battle.push_back(test.number_of_CD_battle());
            DD_battle.push_back(test.number_of_DD_battle());
        }
        test.optimize();
        C_strategy.push_back(test.number_of_C_strategy());
        D_strategy.push_back(test.number_of_D_strategy());
        TFT_strategy.push_back(test.number_of_TFT_strategy());
    }
    
    std::fstream strategy("strategy.csv", std::ios::out);
    std::fstream behavior("battle_behavior.csv", std::ios::out);

    strategy << "C,D,TFT\n";
    for (int i = 0; i < C_strategy.size(); i++) {
        strategy << C_strategy[i] << ",";
        strategy << D_strategy[i] << ",";
        strategy << TFT_strategy[i] << "\n";
    }

    behavior << "C,D,CC,CD,DD\n";
    for (int i = 0; i < C_behavior.size(); i++) {
        behavior << C_behavior[i] << ",";
        behavior << D_behavior[i] << ",";
        behavior << CC_battle[i] << ",";
        behavior << CD_battle[i] << ",";
        behavior << DD_battle[i] << "\n";
    }

    strategy.close();
    behavior.close();
}