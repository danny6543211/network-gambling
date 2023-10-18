#ifndef RAND_H
#define RAND_H

#include <random>
#include <ctime>

#define RAND_TOP 100

std::mt19937 mt(time(NULL));  
std::uniform_int_distribution<size_t> dist(0, RAND_TOP); 
// 均匀取0~99随机数 
inline size_t get_random() {
    return dist(mt);
}

#endif