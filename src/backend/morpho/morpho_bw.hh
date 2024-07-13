#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint8_t* dilation_bw(const Image& img, const morpho_shape& shape);
uint8_t* erosion_bw(const Image& img, const morpho_shape& shape);
uint8_t* open_morpho_bw(const Image& img, const morpho_shape& shape);
uint8_t* close_morpho_bw(const Image& img, const morpho_shape& shape);