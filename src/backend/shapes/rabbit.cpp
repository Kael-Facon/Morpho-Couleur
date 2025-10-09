#include <cmath>

#include "shape.hh"

inline float rabbit(float size, int x, int y)
{
    // Dot
    float len = std::sqrt((x * x) + (y * y));
    float dot_ = x / len;

    float pi = 1.570796;
    float theta = pi - std::acos(dot_);

    float position = (size / 2.) * (+ std::sin(5 * theta)
                                        - std::sin(theta)
                                        - std::cos(2 * theta)
                                        - std::cos(4 * theta));

    return position;
}

void morpho_shape::compute_rabbit()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int a = i - (radius * 1.25);
            int b = j - radius + 1;
            int dist = a * a + b * b;

            float ears = rabbit(radius, a, b);
            float face = radius * 7 / 12.;

            if (ears > 0 && dist <= ears * ears || dist <= face * face)
                mask[j + (size - i) * size] = true;
        }
}