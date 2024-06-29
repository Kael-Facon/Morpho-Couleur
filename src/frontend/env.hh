#pragma once

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

#include "../backend/intersection/intersection.hh"
#include "../backend/image/image.hh"

class Env {
public:
    GLuint render_image{};
    Image *image;

    Env();
    explicit Env(const char* filename);

    void create_texture();
    void render();
};
