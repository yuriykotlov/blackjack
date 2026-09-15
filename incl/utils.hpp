#pragma once

#include <random>

int get_random_int(int min, int max){
    static std::mt19937 gen( std::random_device{}() );
    return std::uniform_int_distribution<int>(min, max)(gen);
}