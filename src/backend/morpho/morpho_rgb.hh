#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

uint8_t* erosion_rgb(const Image& img, const morpho_shape& shape);
uint8_t* dilation_rgb(const Image& img, const morpho_shape& shape);
uint8_t* open_morpho_rgb(const Image& img, const morpho_shape& shape);
uint8_t* close_morpho_rgb(const Image& img, const morpho_shape& shape);
