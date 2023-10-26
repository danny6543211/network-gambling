#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <random>
#include <ctime>

namespace ngl {

class RandomGenerator {
private:
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> int_dist;
    static std::uniform_real_distribution<double> real_dist;

public:
    RandomGenerator() {
        mt = std::mt19937(static_cast<std::mt19937::result_type>(std::time(nullptr)));
        int_dist = std::uniform_int_distribution<int>(0, INT_MAX);
        real_dist = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    static int getRandomInt() {
        return int_dist(mt);
    }

    static double getRandomDouble() {
        return real_dist(mt);
    }
};

// Initialize static members
std::mt19937 RandomGenerator::mt(static_cast<std::mt19937::result_type>(std::time(nullptr)));
std::uniform_int_distribution<int> RandomGenerator::int_dist(0, INT_MAX);
std::uniform_real_distribution<double> RandomGenerator::real_dist(0.0, 1.0);


}

#endif
