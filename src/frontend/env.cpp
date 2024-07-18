#include "env.hh"

int render_count = 0;

Env::Env() {
    image = slides[index_image];
    shape = morpho_shape();
    render();
    create_texture();
}

void Env::change_image() {
    if (index_image == NB_IMAGES)
        index_image = 0;
    if (index_image < 0)
        index_image = NB_IMAGES - 1;
    image = slides[index_image];
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

void Env::morpho(uint8_t *(*method)(const Image& image_, const morpho_shape& shape_))
{
    uint8_t* res = method(*image, shape);
    image->update_char_data(res);
    free(res);
    render();
}

void Env::morpho_lab(uint8_t *(*method)(const Image& image_, rgb24 color, const morpho_shape& shape_), uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t* res = method(*image, {r, g, b}, shape);
    image->update_char_data(res);
    free(res);
    render();
}
