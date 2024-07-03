#include "shape.hh"

#include <cstring>

morpho_shape::morpho_shape()
{
    radius = 5;
    size = 2 * radius - 1;
    t = type::DISK;
    compute_shape();
}

morpho_shape::morpho_shape(int radius_, type t_)
{
    radius = radius_;
    size = 2 * radius - 1;
    t = t_;
    compute_shape();
}

void morpho_shape::set_radius(int radius_)
{
    radius = radius_;
    size = 2 * radius - 1;
    compute_shape();
}

void morpho_shape::set_type(type t_)
{
    t = t_;
    compute_shape();
}


// Generic
void morpho_shape::compute_shape()
{
    mask = (bool*) realloc(mask, size * size * sizeof(bool));
    memset(mask, 0, size * size * sizeof(bool));

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
    
    case BOW_TIE:
        compute_bow_tie(); break;

    case RABBIT:
        compute_rabbit(); break;
    
    // By default; disk
    default:
        compute_disk(); break;
    }
}
