#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint8_t dilation(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape);
uint8_t erosion(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape);
uint8_t* open_morpho(const Image& img, const morpho_shape& shape);
uint8_t* close_morpho(const Image& img, const morpho_shape& shape);