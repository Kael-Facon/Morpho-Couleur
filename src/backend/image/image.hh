#pragma once

#include <vector>
#include <fstream>
#include <thread>
#include "../intersection/intersection.hh"
#include "../utils/utils.hh"

#define PI 3.14159265f

enum IMAGE_TYPE {
    RGB,
    HSV,
    GRAY,
    NONE
};

enum IMAGE_CHANNEL
{
    R = 0,
    G = 1,
    B = 2,
};

class Image {
public:
    int width = 0;
    int height = 0;
    IMAGE_TYPE image_type = IMAGE_TYPE::RGB;
    std::vector<std::vector<Color>> data;
    unsigned char* char_data;

    Image();
    Image(int width_, int height_);

    void update_char_data();
    void update_char_data(unsigned int i, unsigned int j);
    void update_char_data(unsigned int i, unsigned int j, Color c);
    void update_char_data(unsigned char *data, bool gray=false);

    void update_color_data();

    void convert_image(IMAGE_TYPE new_type);
    void convert_thread(IMAGE_TYPE new_type, int start, int end);

    std::vector<std::vector<unsigned int>> get_histogram();

    void to_gray();
    void to_gray(float r_ratio, float g_ratio, float b_ratio);

    uint8_t* get_gray() const;
    uint8_t* get_gray(float r_ratio, float g_ratio, float b_ratio) const;

    uint8_t* get_char_data_copy() const;

    uint8_t* get_channel(IMAGE_CHANNEL chan);

    void save_as_ppm(const std::string& pathname);
};

struct rgb24
{
    uint8_t* r;
    uint8_t* g;
    uint8_t* b;
};

Image *load_image(const std::string& path_name);
