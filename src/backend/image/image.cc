//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#include "image.hh"
#include <cstdlib>
#include <iostream>


namespace tifo {

gray8_image::gray8_image(int _sx, int _sy) {
    sx = _sx;
    sy = _sy;

    length = sx*sy;
    pixels = (GRAY8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);
}

gray8_image::~gray8_image() {
  free(pixels);
}

const GRAY8& gray8_image::get_buffer() const {
    return pixels;
}

GRAY8& gray8_image::get_buffer() {
    return pixels;
}

rgb24_image::rgb24_image(int _sx, int _sy) {
    sx = _sx;
    sy = _sy;

    length = sx*sy*3;
    pixels = (RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);
}

rgb24_image::rgb24_image(const gray8_image& r, const gray8_image& g, const gray8_image& b)
{
    sx = r.sx;
    sy = r.sy;

    length = sx*sy*3;
    pixels = (RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);

    for (int i = 0; i < r.length; i++)
    {
        pixels[i * 3] = r.pixels[i];
        pixels[i * 3 + 1] = g.pixels[i];
        pixels[i * 3 + 2] = b.pixels[i];
    }
}


rgb24_image::~rgb24_image() {
  free(pixels);
}

const RGB8& rgb24_image::get_buffer() const {
    return pixels;
}

RGB8& rgb24_image::get_buffer() {
    return pixels;
}


gray8_image rgb24_image::get_channel(int j) const
{
    gray8_image img = gray8_image(sx, sy);

    for (int i = 0; i < img.length; i++)
        img.pixels[i] = this->pixels[i * 3 + j];

    return img;
}

gray8_image rgb24_image::get_red_channel() const { return get_channel(0); }
gray8_image rgb24_image::get_green_channel() const { return get_channel(1); }
gray8_image rgb24_image::get_blue_channel() const { return get_channel(2); }

void convert_hsv(uint8_t* r_, uint8_t* g_, uint8_t* b_)
{
    float r = *r_ / 255.0f;
    float g = *g_ / 255.0f;
    float b = *b_ / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = std::max(r, std::max(g, b));
    float min = std::min(r, std::min(g, b));

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    *r_ = (uint8_t)(h / 2);   // dst_h : 0-180
    *g_ = (uint8_t)(s * 255); // dst_s : 0-255
    *b_ = (uint8_t)(v * 255); // dst_v : 0-255
}


void convert_rgb(uint8_t* h_, uint8_t* s_, uint8_t* v_)
{
    float h = *h_ *   2.0f; // 0-360
    float s = *s_ / 255.0f; // 0.0-1.0
    float v = *v_ / 255.0f; // 0.0-1.0

    float r, g, b; // 0.0-1.0

    int   hi = (int)(h / 60.0f) % 6;
    float f  = (h / 60.0f) - hi;
    float p  = v * (1.0f - s);
    float q  = v * (1.0f - s * f);
    float t  = v * (1.0f - s * (1.0f - f));

    switch(hi) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        default: r = v, g = p, b = q; break;
    }

    *h_ = (uint8_t)(r * 255); // dst_r : 0-255
    *s_ = (uint8_t)(g * 255); // dst_r : 0-255
    *v_ = (uint8_t)(b * 255); // dst_r : 0-255
}

}
