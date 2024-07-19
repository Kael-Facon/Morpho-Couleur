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

inline bool isFullscreen = true;
inline GLFWwindow* window = nullptr;
inline GLFWmonitor* monitor = nullptr;
inline const GLFWvidmode* mode = nullptr;

#define NB_IMAGES 5
//#define NB_DEMOs 4
inline std::string slides_path[NB_IMAGES] = {
//        "../data/1.ppm",
//        "../data/2.ppm",
//        "../data/3.ppm",
//        "../data/4.ppm",
//        "../data/5.ppm",
//        "../data/6.ppm",
//        "../data/7.ppm",
//        "../data/8.ppm",
//        "../data/9.ppm",
//        "../data/10.ppm",
//        "../data/11.ppm",
//        "../data/12.ppm",
//        "../data/13.ppm",
//        "../data/14.ppm",
//        "../data/15.ppm",
//        "../data/16.ppm",
//        "../data/17.ppm",
//        "../data/18.ppm",
        "../data/morpho_couleur.ppm",
        "../data/sunset.ppm",
        "../data/synthwave.ppm",
        "../data/space.ppm",
        "../data/sf_lsd.ppm",
};
//inline std::string demo_path[NB_DEMOs] = {
//    "../data/morpho_couleur.ppm",
//    "../data/sunset.ppm",
////    "../data/space.ppm",
//    "../data/synthwave.ppm",
////    "../data/sf_lsd.ppm"
//};
inline Image *slides[NB_IMAGES] = {
        load_image(slides_path[0]),
        load_image(slides_path[1]),
        load_image(slides_path[2]),
        load_image(slides_path[3]),
        load_image(slides_path[4]),
//        load_image(slides_path[5]),
//        load_image(slides_path[6]),
//        load_image(slides_path[7]),
//        load_image(slides_path[8]),
//        load_image(slides_path[9]),
//        load_image(slides_path[10]),
//        load_image(slides_path[11]),
//        load_image(slides_path[12]),
//        load_image(slides_path[13]),
//        load_image(slides_path[14]),
//        load_image(slides_path[15]),
//        load_image(slides_path[16]),
//        load_image(slides_path[17]),
//        load_image(slides_path[18]),
//        load_image(slides_path[19]),
//        load_image(slides_path[20]),
//        load_image(slides_path[21]),
//        load_image(slides_path[22]),
};
inline int index_image = 0;
inline bool demo = false;

class Env {
public:
    GLuint render_image{};
    Image *image;
    int form = 0;
    int size = 1;
    morpho_shape shape;

    Env();

    void change_image();
    void create_texture();
    void render();

    void morpho(uint8_t *(*method)(const Image& image_, const morpho_shape& shape_));
    void morpho_lab(uint8_t *(*method)(const Image& image_, rgb24 color, const morpho_shape& shape_), uint8_t r, uint8_t g, uint8_t b);
};