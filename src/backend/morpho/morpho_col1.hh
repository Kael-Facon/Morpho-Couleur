#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint8_t* erosion_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* dilation_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* close_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
