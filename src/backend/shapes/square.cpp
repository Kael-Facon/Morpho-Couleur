#include "shape.hh"

void morpho_shape::compute_square()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mask[i + j * size] = true;
}