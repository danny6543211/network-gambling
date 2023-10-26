#ifndef GAME_METHOD_HPP
#define GAME_METHOD_HPP

#include "Strategy.hpp"

namespace ngl {

namespace GamblingMethod {

struct SnowdriftDilemma {};
struct PrisonersDilemma {};

}

using GamblingMethod::SnowdriftDilemma;
using GamblingMethod::PrisonersDilemma;
    
inline void _battle(Action xAction, Action yAction, 
    double& xPayoff, double& yPayoff, double r, PrisonersDilemma) {
 
    if (xAction == yAction) {
        if (xAction == Action::Cooperate) {
            xPayoff += 1;
            yPayoff += 1;
        }
        else 
            ;
    }
    else {
        if (xAction == Action::Defect) {
            xPayoff += 1 + r;
        }
        else {
            yPayoff += 1 + r;
        }
    }    
}

inline void _battle(Action xAction, Action yAction, 
    double& xPayoff, double& yPayoff, double r, SnowdriftDilemma) {

    if (xAction == yAction) {
        if (xAction == Action::Cooperate) {
            xPayoff += 1;
            yPayoff += 1;
        }
        else 
            ;
    }
    else {
        if (xAction == Action::Defect) {
            xPayoff += 1 + r;
            yPayoff += 1 - r;
        }
        else {
            xPayoff += 1 - r;
            yPayoff += 1 + r;
        }
    }
}

template<class GamblingMethodType>
inline void battle(Action xAction, Action yAction, 
    double& xPayoff, double& yPayoff, double r, GamblingMethodType) {

    return _battle(xAction, yAction, xPayoff, yPayoff, r, GamblingMethodType());
}


} /* End of namespace ngl */

#endif