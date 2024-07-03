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
        BOW_TIE,
        RABBIT,
    };

    int radius = 5;
    int size;
    type t;
    bool* mask = nullptr; 

    morpho_shape();
    morpho_shape(int radius, type t_);
    ~morpho_shape() = default;

    void set_radius(int radius_);
    void set_type(type t_);

    // Generic
    void compute_shape();

private:
    // Specific
    void compute_disk();
    void compute_diamond();
    void compute_square();
    void compute_morpho();
    void compute_bow_tie();
    void compute_rabbit();
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
