#pragma once

#include <stdint.h>

#include "shape.hh"
#include "../utils/utils.hh"

static bool morpho_diamond[MORPHO_SIZE][MORPHO_SIZE] = {false};


inline void create_diamond()
{
    for (int i = 0; i < MORPHO_SIZE; i++)
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            int a = abs<int>(i - MORPHO_RADIUS + 1);
            int b = abs<int>(j - MORPHO_RADIUS + 1);
        
            if (a + b < MORPHO_RADIUS)
                morpho_diamond[i][j] = true;
        }
}