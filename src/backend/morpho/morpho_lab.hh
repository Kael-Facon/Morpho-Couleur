#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"
#include "../utils/color_lab.hh"

uint8_t* erosion_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* dilation_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* close_morpho_lab(const Image& img, rgb24 color, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
