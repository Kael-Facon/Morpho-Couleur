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

class Image {
public:
    int width = 0;
    int height = 0;
    IMAGE_TYPE image_type = IMAGE_TYPE::RGB;
    std::vector<std::vector<Color>> data;
    unsigned char* char_data;

    Image();
    Image(int width_, int height_);

    void update_char_data(unsigned int i, unsigned int j);
    void update_char_data(unsigned int i, unsigned int j, Color c);

    void convert_image(IMAGE_TYPE new_type);
    void convert_thread(IMAGE_TYPE new_type, int start, int end);

    std::vector<std::vector<unsigned int>> get_histogram();

    void save_as_ppm(const std::string& pathname);
};

Image *load_image(const std::string& path_name);