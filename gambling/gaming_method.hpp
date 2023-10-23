#ifndef GAMEING_METHOD_HPP
#define GAMEING_METHOD_HPP

#include "behavior.hpp"

namespace gaming_method {
    struct snowdrift_dilemma {};
    struct prisoners_dilemma {};
};

inline void __snowdrift_dilemma(behavior x_behavior, behavior y_behavior, 
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

inline void __prisoners_dilemma(behavior x_behavior, behavior y_behavior, 
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

inline void __battle(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r, gaming_method::snowdrift_dilemma) {
        __snowdrift_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
}

inline void __battle(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r, gaming_method::prisoners_dilemma) {
        __prisoners_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
}

template<class GamingMethodType>
inline void battle(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r, GamingMethodType) {
        __battle(x_behavior, y_behavior, x_payoff, y_payoff, r, GamingMethodType());
}

#endif