#pragma once

#include <vector>
#include <fstream>
#include <thread>
#include "../intersection/intersection.hh"
#include "../utils/utils.hh"

#define PI 3.14159265f

class Image {
public:
    int width = 0;
    int height = 0;
    std::vector<std::vector<Color>> data;
    unsigned char* char_data;
    std::vector<std::vector<bool>> selected;

    Image()= default;
    Image(int width_, int height_);

    static Color bg_color(Image *bg, Vector3 dir);
    void update_char_data(unsigned int i, unsigned int j);
    void update_char_data(unsigned int i, unsigned int j, Color c);
    void render(Image *bg);
    void render_thread(Image *bg, int start, int end);

    void save_as_ppm(const std::string& pathname);
};

Image *load_image(const std::string& path_name);