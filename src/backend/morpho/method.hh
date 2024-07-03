#pragma once

#include <stdint.h>
#include "../shapes/shape.hh"
#include "../image/image.hh"

// Generic method for erosion and dilation
bool erosion_(uint8_t buffer_val, uint8_t value);
bool dilation_(uint8_t buffer_val, uint8_t value);
uint64_t get_morpho_pos(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape, bool (*method)(uint8_t buffer_val, uint8_t value));
uint8_t* get_morpho(uint8_t* src_buffer, uint8_t* gray_buffer, int width, int height, const morpho_shape& shape, bool (*method)(uint8_t buffer_val, uint8_t value));