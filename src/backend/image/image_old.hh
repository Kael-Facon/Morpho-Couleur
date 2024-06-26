#pragma once

#include <vector>
#include <fstream>
#include <thread>

class Image {
    public:
        int width = 0;
        int height = 0;

        Image()= default;
        Image(int width_, int height_);

        void save_as_ppm(const std::string& pathname);
};

Image load_image(const std::string& path_name);