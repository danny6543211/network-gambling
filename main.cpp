#include <iostream>
#include "BA_network.hpp"

int main() {
    __BA_network<int> a(10, 1);

    std::cout << a.degree_of_network();   
    
}