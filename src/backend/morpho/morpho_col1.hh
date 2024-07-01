#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint64_t dilation_col1_(uint8_t* gray_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* dilation_col1(uint8_t* color_buffer, uint8_t* gray_buffer, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint64_t erosion_col1_(uint8_t* gray_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* erosion_col1(uint8_t* color_buffer, uint8_t* gray_buffer, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* close_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
