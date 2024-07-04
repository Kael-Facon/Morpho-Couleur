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
#include "../backend/shapes/disk.hh"
#include "../backend/shapes/diamond.hh"
#include "../backend/shapes/square.hh"

class Env {
public:
    GLuint render_image{};
    Image *image;
    int form = 0;
    int size = 1;

    Env();
    explicit Env(const char* filename);

    void create_texture();
    void render();
};