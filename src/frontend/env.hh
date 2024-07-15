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

    void rgb_dilation();
    void rgb_erosion();

    void hsv_dilation_s();
    void hsv_erosion_s();

    void hsv_dilation_v();
    void hsv_erosion_v();

    void hsv_dilation_sv();
    void hsv_erosion_sv();

    void lab_dilation(uint8_t r, uint8_t g, uint8_t b);
    void lab_erosion(uint8_t r, uint8_t g, uint8_t b);

    void bw_dilation();
    void bw_erosion();

    void bw_open();
    void bw_close();
};