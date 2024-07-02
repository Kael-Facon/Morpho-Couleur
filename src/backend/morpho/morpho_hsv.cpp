#include <stdint.h>

#include "method.hh"
#include "../shapes/shape.hh"
#include "../utils/color_hsv.hh"


uint8_t* erosion_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* dilation_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* open_morpho_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* close_morpho_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_saturation_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* erosion_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer =  get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* dilation_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* open_morpho_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    free(sat_buffer);

    return color_buffer;
}

uint8_t* close_morpho_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* sat_buffer = get_hsv_value_map(img);
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, dilation_);

    // Erosion
    color_buffer = get_morpho(color_buffer, sat_buffer, img.width, img.height, morpho_shape, erosion_);

    free(sat_buffer);

    return color_buffer;
}