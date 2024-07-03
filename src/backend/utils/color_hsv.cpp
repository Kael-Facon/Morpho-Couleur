#include <cmath>

#include "color_hsv.hh"

hsv rbg_to_hsv(uint8_t r_, uint8_t g_, uint8_t b_)
{
    float max_color = std::max(std::max(r_, g_), b_);
    float min_color = std::min(std::min(r_, g_), b_);
    float max_min = max_color - min_color;

    hsv new_hsv;

    if (max_min == 0)
        new_hsv.h = 0; // h
    else if (max_color == r_)
        new_hsv.h = (g_ - b_)/max_min; // h
    else if (max_color == g_)
        new_hsv.h = 2.0f + (b_ - r_)/max_min; // h
    else // (max_color == c.b)
        new_hsv.h = 4.0f + (r_ - g_)/max_min; // h
    new_hsv.h *= 30; // h

    if (new_hsv.h < 0)
        new_hsv.h += 179;
    if (new_hsv.h >= 179)
        new_hsv.h -= 179;

    new_hsv.s = 0; // s
    if (max_color != 0)
        new_hsv.s = static_cast<uint8_t>((1 - min_color / max_color) * 255); // s
    new_hsv.v = max_color; // v

    return new_hsv;
}

hsv rbg_to_hsv(rgb24 rgb)
{
    return rbg_to_hsv(rgb.r, rgb.g, rgb.b);
}

hsv* get_hsv_buffer(rgb24* rgb_buffer, int width, int height)
{
    hsv* hsv_buffer = (hsv*) malloc(width * height * sizeof(hsv));

    for (int i = 0; i < width; i++) 
        for (int j = 0; j < height; j++)
            hsv_buffer[i + j * width] = rbg_to_hsv(rgb_buffer[i + j * width]);

    return hsv_buffer;
}

uint8_t* get_hsv_saturation_map(const Image& img)
{
    rgb24* rgb_buffer = (rgb24*) img.get_char_data_copy();
    hsv* hsv_buffer = get_hsv_buffer(rgb_buffer, img.width, img.height);

    uint8_t* saturation_map = (uint8_t*) malloc(img.width * img.height * sizeof(uint8_t));

    for (int i = 0; i < img.width; i++) 
        for (int j = 0; j < img.height; j++)
            saturation_map[i + j * img.width] = hsv_buffer[i + j * img.width].s;
    
    free(rgb_buffer);
    free(hsv_buffer);

    return saturation_map;
}

uint8_t* get_hsv_value_map(const Image& img)
{
    rgb24* rgb_buffer = (rgb24*) img.get_char_data_copy();
    hsv* hsv_buffer = get_hsv_buffer(rgb_buffer, img.width, img.height);

    uint8_t* saturation_map = (uint8_t*) malloc(img.width * img.height * sizeof(uint8_t));

    for (int i = 0; i < img.width; i++) 
        for (int j = 0; j < img.height; j++)
            saturation_map[i + j * img.width] = hsv_buffer[i + j * img.width].v;
    
    free(rgb_buffer);
    free(hsv_buffer);

    return saturation_map;
}

uint8_t* get_hsv_saturation_value_map(const Image& img)
{
    rgb24* rgb_buffer = (rgb24*) img.get_char_data_copy();
    hsv* hsv_buffer = get_hsv_buffer(rgb_buffer, img.width, img.height);

    uint8_t* saturation_map = (uint8_t*) malloc(img.width * img.height * sizeof(uint8_t));

    for (int i = 0; i < img.width; i++) 
        for (int j = 0; j < img.height; j++)
            saturation_map[i + j * img.width] = (hsv_buffer[i + j * img.width].v / 255.) * (hsv_buffer[i + j * img.width].s / 255.) * 255;
    
    free(rgb_buffer);
    free(hsv_buffer);

    return saturation_map;
}

uint8_t* get_hsv_saturation_value_map_coef(const Image& img, float coef_sat)
{
    rgb24* rgb_buffer = (rgb24*) img.get_char_data_copy();
    hsv* hsv_buffer = get_hsv_buffer(rgb_buffer, img.width, img.height);

    uint8_t* saturation_map = (uint8_t*) malloc(img.width * img.height * sizeof(uint8_t));

    for (int i = 0; i < img.width; i++) 
        for (int j = 0; j < img.height; j++)
            saturation_map[i + j * img.width] = (hsv_buffer[i + j * img.width].v * (1 - coef_sat)) + (hsv_buffer[i + j * img.width].s * coef_sat);
    
    free(rgb_buffer);
    free(hsv_buffer);

    return saturation_map;
}