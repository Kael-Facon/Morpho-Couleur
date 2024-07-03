#include <stdint.h>

#include "method.hh"
#include "../shapes/shape.hh"
#include "../utils/color_hsv.hh"

/// Saturation

uint8_t* erosion_hsv_s(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* dilation_hsv_s(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* open_morpho_hsv_s(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* close_morpho_hsv_s(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

///

/// Value

uint8_t* erosion_hsv_v(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* dilation_hsv_v(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* open_morpho_hsv_v(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* close_morpho_hsv_v(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

///

/// Saturation x Value

uint8_t* erosion_hsv_sv(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* dilation_hsv_sv(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* open_morpho_hsv_sv(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* close_morpho_hsv_sv(const Image& img, const morpho_shape& shape)
{
    uint8_t* sat_buffer = get_hsv_saturation_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

///