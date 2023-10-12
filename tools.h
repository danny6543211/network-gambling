#ifndef TOOLS_H
#define TOOLS_H

#include <random>
#include <ctime>

// 随机数引擎
std::random_device rd;
std::mt19937 mt(time(NULL));  // Mersenne Twister 19937 随机数引擎
// 创建随机数分布
std::uniform_int_distribution<int> dist;  // 生成范围在1到6之间的整数

inline size_t get_random() {
    return dist(mt);
}

#endif