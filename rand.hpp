#ifndef RAND_HPP
#define RAND_HPP

#include <random>
#include <ctime>

#define RAND_TOP INT_MAX

std::mt19937 mt(time(NULL));  
std::uniform_int_distribution<int> dist(0, RAND_TOP); 

inline int get_rand_int() {
    return dist(mt);
}

inline double get_rand_p() {
    return get_rand_int() / (double) RAND_TOP;
}

#endif