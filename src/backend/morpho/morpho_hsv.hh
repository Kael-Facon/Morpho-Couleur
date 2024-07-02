#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint8_t* erosion_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* dilation_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* close_morpho_hsv_s(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);

uint8_t* erosion_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* dilation_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* close_morpho_hsv_v(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);