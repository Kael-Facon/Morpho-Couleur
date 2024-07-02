#include <stdint.h>

#include "method.hh"
#include "../shapes/shape.hh"
#include "../utils/color_lab.hh"

uint8_t* erosion_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* dist_buffer = get_lab_distance_map(img, color);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, erosion_);

    free(dist_buffer);

    return color_buffer;
}

uint8_t* dilation_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* dist_buffer = get_lab_distance_map(img, color);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, dilation_);

    free(dist_buffer);

    return color_buffer;
}

uint8_t* open_morpho_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* dist_buffer = get_lab_distance_map(img, color);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, dilation_);

    free(dist_buffer);

    return color_buffer;
}

uint8_t* close_morpho_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* dist_buffer = get_lab_distance_map(img, color);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, dist_buffer, img.width, img.height, morpho_shape, erosion_);

    free(dist_buffer);

    return color_buffer;
}