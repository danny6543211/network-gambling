#ifndef GAME_TYPE_HPP
#define GAME_TYPE_HPP

#include "behavior.hpp"

enum class gaming_method {
    snowdrift_dilemma, prisoners_dilemma
};

void snowdrift_dilemma(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r) {
    
    if (x_behavior == y_behavior) {
        if (x_behavior == behavior::COOPERATE) {
            x_payoff += 1;
            y_payoff += 1;
        }
        else 
            ;
    }
    else {
        if (x_behavior == behavior::BETRAY) {
            x_payoff += 1 + r;
            y_payoff += 1 - r;
        }
        else {
            x_payoff += 1 - r;
            y_payoff += 1 + r;
        }
    }
}

void prisoners_dilemma(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r) {
    
    if (x_behavior == y_behavior) {
        if (x_behavior == behavior::COOPERATE) {
            x_payoff += 1;
            y_payoff += 1;
        }
        else 
            ;
    }
    else {
        if (x_behavior == behavior::BETRAY) {
            x_payoff += 1 + r;
        }
        else {
            y_payoff += 1 + r;
        }
    }    
}

#endif