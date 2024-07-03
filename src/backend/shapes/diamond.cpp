#include "shape.hh"
#include "../utils/utils.hh"

void morpho_shape::compute_diamond()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int a = abs<int>(i - radius + 1);
            int b = abs<int>(j - radius + 1);
        
            if (a + b < radius)
                mask[i + j * size] = true;
        }
}