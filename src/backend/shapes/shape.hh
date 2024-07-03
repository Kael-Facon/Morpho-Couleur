#pragma once

#include <iostream>

class morpho_shape
{
public:
    enum type
    {
        DISK,
        SQUARE,
        DIAMOND,
        MORPHO,
    };

    int radius = 5;
    int  size = 2 * radius - 1;
    type t = type::DISK;
    bool* mask = nullptr; 

    morpho_shape();
    morpho_shape(int radius, type t_);
    ~morpho_shape() = default;

    // Generic
    void compute_shape();

    // Specific
    void compute_disk();
    void compute_diamond();
    void compute_square();
    void compute_morpho();
};

inline std::ostream& operator<<(std::ostream& os, morpho_shape ms)
{
    for (int i = 0; i < ms.size; i++)
    {
        os << ms.mask[i];
        for (int j = 1; j < ms.size; j++)
            os << ' ' << ms.mask[i + ms.size * j];
        os << '\n';
    }

    return os;
}
