#ifndef RAND_H
#define RAND_H

#include <random>
#include <ctime>

#define RAND_TOP INT_MAX

std::mt19937 mt(time(NULL));  
std::uniform_int_distribution<int> dist(0, RAND_TOP); 

inline size_t get_rand_int() {
    return dist(mt);
}

inline double get_rand_p() {
    return get_rand_int() / (double) RAND_TOP;
}

#endif