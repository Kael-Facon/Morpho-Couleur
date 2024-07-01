#pragma once

#include "shape.hh"

static bool morpho_square[MORPHO_SIZE][MORPHO_SIZE] = {true};

void create_square()
{
    for (int i = 0; i < MORPHO_SIZE; i++)
        for (int j = 0; j < MORPHO_SIZE; j++)
            morpho_square[i][j] = true;
}