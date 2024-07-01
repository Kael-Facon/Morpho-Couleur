#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"

uint8_t dilation(uint8_t* gray_buffer, uint8_t* color_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t erosion(uint8_t* gray_buffer, uint8_t* color_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);
uint8_t* open_morpho(uint8_t* gray_buffer, uint8_t* color_buffer, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE]);