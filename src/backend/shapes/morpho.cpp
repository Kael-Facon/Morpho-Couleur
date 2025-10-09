#include <cmath>

#include "shape.hh"

inline float butterfly(float size, int x, int y)
{
    // Dot
    float len = std::sqrt((x * x) + (y * y));
    float dot_ = x / len;

    float pi = 1.570796;
    float theta = pi - std::acos(dot_);

    float position = size * (6 - std::sin(theta)
                               + std::sin(3 * theta)
                               + std::sin(5 * theta)
                               - std::sin(7 * theta)
                               + 3 * std::cos(2 * theta)
                               - 2 * std::cos(4 * theta));

    return position;
}

void morpho_shape::compute_morpho()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int a = i - radius + 1;
            int b = j - radius + 1;

            float butterfly_border = butterfly(radius / (9.), a, b);
        
            if (a * a + b * b <= butterfly_border * butterfly_border)
                mask[j + i * size] = true;
        }
}