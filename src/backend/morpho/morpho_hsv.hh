#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

/* TODO */
uint8_t* erosion_hsv(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
/* TODO */
uint8_t* dilation_hsv(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
/* TODO */
uint8_t* open_morpho_hsv(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
/* TODO */
uint8_t* close_morpho_hsv(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
