#pragma once

#include <random>

inline static std::mt19937 gen( std::random_device{}() );

inline int get_random_int(int min, int max){
    return std::uniform_int_distribution<int>(min, max)(gen);
}