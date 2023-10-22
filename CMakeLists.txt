cmake_minimum_required(VERSION 3.0)

project(network_gambling)

set(CMAKE_CXX_STANDARD 14)

include_directories(network gambling utils)

# 添加可执行文件
add_executable(network_gambling main.cpp)