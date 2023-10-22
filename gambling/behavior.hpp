#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "rand.h"

enum class behavior {
    BETRAY, COOPERATE
};

inline behavior get_rand_behavior() { 
    return (behavior) (get_rand_int() % 2); 
}



#endif