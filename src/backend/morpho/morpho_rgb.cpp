#include <stdint.h>

#include "method.hh"
#include "../shapes/shape.hh"

uint8_t* erosion_rgb(const Image& img, const morpho_shape& shape)
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, erosion_);

    free(gray_buffer);

    return color_buffer;
}

uint8_t* dilation_rgb(const Image& img, const morpho_shape& shape)
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, dilation_);

    free(gray_buffer);

    return color_buffer;
}

uint8_t* open_morpho_rgb(const Image& img, const morpho_shape& shape)
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, dilation_);

    free(gray_buffer);

    return color_buffer;
}

uint8_t* close_morpho_rgb(const Image& img, const morpho_shape& shape)
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, gray_buffer, img.width, img.height, shape, erosion_);

    free(gray_buffer);

    return color_buffer;
}