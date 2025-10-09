#include <cmath>

#include "color_lab.hh"

Lab rbg_to_lab(uint8_t r_, uint8_t g_, uint8_t b_)
{
    double r = static_cast<double>(r_) / 255.0;
    double g = static_cast<double>(g_) / 255.0;
    double b = static_cast<double>(b_) / 255.0;

    // Apply gamma correction
    r = (r > 0.04045) ? std::pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = (g > 0.04045) ? std::pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = (b > 0.04045) ? std::pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

    double X = r * 0.4124 + g * 0.3576 + b * 0.1805;
    double Y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    double Z = r * 0.0193 + g * 0.1192 + b * 0.9505;

    // Convert to Lab color space
    X /= 0.95047;
    Y /= 1.0;
    Z /= 1.08883;

    X = (X > 0.008856) ? std::pow(X, 1.0 / 3.0) : (7.787 * X) + (16.0 / 116.0);
    Y = (Y > 0.008856) ? std::pow(Y, 1.0 / 3.0) : (7.787 * Y) + (16.0 / 116.0);
    Z = (Z > 0.008856) ? std::pow(Z, 1.0 / 3.0) : (7.787 * Z) + (16.0 / 116.0);

    Lab lab;

    lab.L = 116.0 * Y - 16.0;
    lab.a = 500.0 * (X - Y);
    lab.b = 200.0 * (Y - Z);

    return lab;
}

Lab rbg_to_lab(rgb24 rgb)
{
    return rbg_to_lab(rgb.r, rgb.g, rgb.b);
}


// Supposed that max distance in Lab space is 374.2325
uint8_t lab_dist(Lab lab1, Lab lab2)
{
    static double max_dist = 374.2325; 
    double L_diff = std::pow(lab2.L - lab1.L, 2);
    double a_diff = std::pow(lab2.a - lab1.a, 2);
    double b_diff = std::pow(lab2.b - lab1.b, 2);

    // Invert distance the closer to the color the better (so brighter)
    return 255 - ((std::sqrt(L_diff + a_diff + b_diff) * 255) / max_dist);
}

Lab* get_lab_buffer(rgb24* rgb_buffer, int width, int height)
{
    Lab* lab_buffer = (Lab*) malloc(width * height * sizeof(Lab));

    for (int i = 0; i < width; i++) 
        for (int j = 0; j < height; j++)
            lab_buffer[i + j * width] = rbg_to_lab(rgb_buffer[i + j * width]);

    return lab_buffer;
}

uint8_t* get_lab_distance_map(const Image& img, rgb24 compared_rgb_color)
{
    rgb24* rgb_buffer = (rgb24*) img.get_char_data_copy();
    Lab* lab_buffer = get_lab_buffer(rgb_buffer, img.width, img.height);

    Lab compared_Lab = rbg_to_lab(compared_rgb_color);
    uint8_t* distance_map = (uint8_t*) malloc(img.width * img.height * sizeof(uint8_t));

    for (int i = 0; i < img.width; i++) 
        for (int j = 0; j < img.height; j++)
            distance_map[i + j * img.width] = lab_dist(lab_buffer[i + j * img.width], compared_Lab);
    
    free(rgb_buffer);
    free(lab_buffer);

    return distance_map;
}