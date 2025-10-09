#include <cmath>

#include "shape.hh"

inline float bow_tie(float size, int x, int y)
{
    // Dot
    float len = std::sqrt((x * x) + (y * y));
    float dot_ = x / len;

    float pi = 1.570796;
    float theta = pi - std::acos(dot_);

    float position = size * (6 + 4 * std::cos(2 * theta)
                               - 0.9 * std::cos(4 * theta)
                               - std::cos(6 * theta));

    return position;
}

void morpho_shape::compute_bow_tie()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int a = i - radius + 1;
            int b = j - radius + 1;

            float border = bow_tie(radius / (9.), a, b);
        
            if (a * a + b * b <= border * border)
                mask[j + i * size] = true;
        }
}