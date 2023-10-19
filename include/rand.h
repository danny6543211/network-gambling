#ifndef RAND_H
#define RAND_H

#include <random>
#include <ctime>

#define RAND_TOP INT_MAX

std::mt19937 mt(time(NULL));  
std::uniform_int_distribution<int> dist(0, INT_MAX); 
// 均匀取0~99随机数 
inline size_t get_rand_int() {
    return dist(mt);
}

inline double get_rand() {
    return get_rand_int() / (double) INT_MAX;
}

#endif