#pragma once

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

#include "../backend/intersection/intersection.hh"
#include "../backend/image/image.hh"

#include "../backend/morpho/morpho_rgb.hh"
#include "../backend/morpho/morpho_lab.hh"
#include "../backend/morpho/morpho_hsv.hh"
#include "../backend/morpho/morpho_bw.hh"

#define WIDTH 1920
#define HEIGHT 1080

class Env {
public:
    GLuint render_image{};
    Image *image;
    int form = 0;
    int size = 1;
    morpho_shape shape;

    Env();
    explicit Env(const char* filename);

    void create_texture();
    void render();

    void morpho(uint8_t *(*method)(const Image& image_, const morpho_shape& shape_));
    void morpho_lab(uint8_t *(*method)(const Image& image_, rgb24 color, const morpho_shape& shape_), uint8_t r, uint8_t g, uint8_t b);
};