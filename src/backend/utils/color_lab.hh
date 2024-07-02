#pragma once

#include <stdint.h>
#include "../image/image.hh"

struct Lab
{
    uint8_t L; // 0 - 100
    char a; // -127 - 128
    char b; // -127 - 128
};


Lab rbg_to_lab(uint8_t r, uint8_t g, uint8_t b);
Lab rbg_to_lab(rgb24 rgb);
uint8_t lab_dist(Lab lab1, Lab lab2);
Lab* get_lab_buffer(rgb24* rgb_buffer, int width, int height);
uint8_t* get_lab_distance_map(const Image& img, rgb24 compared_rgb_color);