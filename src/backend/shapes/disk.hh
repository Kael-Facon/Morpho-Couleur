#pragma once

#include <stdint.h>

#include "shape.hh"

static bool morpho_disk[MORPHO_SIZE][MORPHO_SIZE] = {false};

inline void create_disk()
{
    for (int i = 0; i < MORPHO_SIZE; i++)
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            int a = i - MORPHO_RADIUS + 1;
            int b = j - MORPHO_RADIUS + 1;
        
            if (a * a + b * b < MORPHO_RADIUS * MORPHO_RADIUS)
                morpho_disk[i][j] = true;
        }
}