#include "env.hh"

int render_count = 0;

Env::Env() {
    image = new Image();
    shape = morpho_shape();
    render();
    create_texture();
}

Env::Env(const char* filename) {
    image = load_image(filename);
    shape = morpho_shape();
    render();
    create_texture();
}

void Env::create_texture() {
    unsigned char* image_data = image->char_data;
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);

    glDeleteTextures(1, &render_image);
    render_image = image_texture;
}

void Env::render() {
    render_count++;
    std::cout  << "Rendering " << render_count << "\n";
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->char_data);
}

void Env::bw_dilation() {
//        image->update_char_data(res);
//        render();
//        uint8_t* res = dilation_rgb(*image, morpho_disk);
}

void Env::bw_erosion() {
//        image->update_char_data(res);
//        render();
//        uint8_t* res = dilation_rgb(*image, morpho_disk);
}

void Env::rgb_dilation() {
    uint8_t* res = dilation_rgb(*image, shape);
    image->update_char_data(res);
    render();
}

void Env::rgb_erosion() {
    uint8_t* res = erosion_rgb(*image, shape);
    image->update_char_data(res);
    render();
}

void Env::hsv_dilation_s() {
    uint8_t* res = dilation_hsv_s(*image, shape);
    image->update_char_data(res);
    render();
}

void Env::hsv_erosion_s() {
    uint8_t *res = erosion_hsv_s(*image, shape);
    image->update_char_data(res);
    render();
}

void Env::hsv_dilation_v() {
    uint8_t* res;
    if (form == 0)
        res = dilation_hsv_v(*image, shape);

    image->update_char_data(res);
    render();
}

void Env::hsv_erosion_v() {
    uint8_t* res;
    if (form == 0)
        res = erosion_hsv_v(*image, shape);
    else if (form == 1)
        res = erosion_hsv_v(*image, shape);
    else
        res = erosion_hsv_v(*image, shape);

    image->update_char_data(res);
    render();
}

void Env::hsv_dilation_sv() {
//        image->update_char_data(res);
//        render();
}

void Env::hsv_erosion_sv() {
//        image->update_char_data(res);
//        render();
}

void Env::lab_dilation() {
    uint8_t* res = dilation_lab(*image, {255, 0, 0}, shape);
    image->update_char_data(res);
    render();
}

void Env::lab_erosion() {
    uint8_t* res = erosion_lab(*image, {255, 0, 0}, shape);
    image->update_char_data(res);
    render();
}

