#ifndef GAMEING_METHOD_HPP
#define GAMEING_METHOD_HPP

#include "behavior.hpp"

enum class gaming_method_type {
    snowdrift_dilemma, prisoners_dilemma
};

inline void snowdrift_dilemma(behavior x_behavior, behavior y_behavior, 
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

inline void prisoners_dilemma(behavior x_behavior, behavior y_behavior, 
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

void battle(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r, gaming_method_type method) {
        if (method == gaming_method_type::snowdrift_dilemma)
            snowdrift_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
        else if (method == gaming_method_type::prisoners_dilemma)
            prisoners_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
        else
            throw "Method is not impletment";
    }

#endif