#include "shape.hh"

morpho_shape::morpho_shape()
{
    compute_shape();
}

morpho_shape::morpho_shape(int radius_, type t_)
{
    radius = radius_;
    size = 2 * radius - 1;
    t = t_;
    compute_shape();
}

// Generic
void morpho_shape::compute_shape()
{
    if (mask)
        free(mask);
    mask = (bool*) calloc(size * size, sizeof(bool));

    switch (t)
    {
    case DISK:
        compute_disk(); break;

    case SQUARE:
        compute_square(); break;

    case DIAMOND:
        compute_diamond(); break;

    case MORPHO:
        compute_morpho(); break;
    
    // By default; disk
    default:
        compute_disk(); break;
    }
}
