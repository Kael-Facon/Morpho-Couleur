#include "shape.hh"

void morpho_shape::compute_disk()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int a = i - radius + 1;
            int b = j - radius + 1;
        
            if (a * a + b * b < radius * radius)
                mask[i + j * size] = true;
        }
}