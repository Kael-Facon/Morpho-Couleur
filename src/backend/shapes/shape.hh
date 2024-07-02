#pragma once

#include <iostream>

#define MORPHO_RADIUS 5
#define MORPHO_SIZE MORPHO_RADIUS + MORPHO_RADIUS - 1

inline std::ostream& operator<<(std::ostream& os, bool shape[MORPHO_SIZE][MORPHO_SIZE])
{
    for (int i = 0; i < MORPHO_SIZE; i++)
    {
        os << shape[i][0];
        for (int j = 1; j < MORPHO_SIZE; j++)
            os << ' ' << shape[i][j];
        os << '\n';
    }

    return os;
}

inline void print_shape(bool shape[MORPHO_SIZE][MORPHO_SIZE])
{
    std::cout << shape;
}