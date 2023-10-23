#ifndef GAMBLING_HPP
#define GAMBLING_HPP

#include "rand.hpp"

namespace gambling {

enum class strategy {
    DEFECTION, COOPERATION, TFT
};

inline strategy get_rand_strategy() {
    return (strategy) (get_rand_int() % 3);
}

enum class behavior {
    DEFECT, COOPERATE
};

inline behavior get_rand_behavior() { 
    return (behavior) (get_rand_int() % 2); 
}

enum class gambling_method {
    snowdrift_dilemma, prisoners_dilemma
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
        if (x_behavior == behavior::DEFECT) {
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
        if (x_behavior == behavior::DEFECT) {
            x_payoff += 1 + r;
        }
        else {
            y_payoff += 1 + r;
        }
    }    
}

inline void battle(behavior x_behavior, behavior y_behavior, 
    double& x_payoff, double& y_payoff, double r, gambling_method gambling_method) {
        if (gambling_method == gambling_method::prisoners_dilemma)
            __prisoners_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
        else if (gambling_method == gambling_method::snowdrift_dilemma) 
            __snowdrift_dilemma(x_behavior, y_behavior, x_payoff, y_payoff, r);
        else
            throw "This gambling method is not implement";
}


}

#endif