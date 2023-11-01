#ifndef GAME_METHOD
#define GAME_METHOD

#include "Action.hpp"
#include "RandomGenerator.hpp"

namespace ngl {

struct PrisonersDilemma {
    static void battle(Action xAction, Action yAction, 
        double& xPayoff, double& yPayoff, double r) {
            
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
};

struct SnowdriftDilemma {
    static void battle(Action xAction, Action yAction, 
        double& xPayoff, double& yPayoff, double r) {
        
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
};

namespace gm {
    using ngl::PrisonersDilemma;
    using ngl::SnowdriftDilemma;
} 

}   /* End of namespace ngl */

#endif