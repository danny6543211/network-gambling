#pragma once

#include "Action.hpp"
#include "RandomGenerator.hpp"

namespace ngl {

namespace GameMethod {

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

}   /* End of namespace GameMethod */

}   /* End of namespace ngl */