#include "method.hh"

// Generic method for erosion and dilation
bool erosion_(uint8_t buffer_val, uint8_t value) { return buffer_val < value; }
bool dilation_(uint8_t buffer_val, uint8_t value) { return buffer_val > value; }

uint64_t get_morpho_pos(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape, bool (*method)(uint8_t buffer_val, uint8_t value))
{
    uint8_t value = gray_buffer[x + width * y];
    uint64_t pos = x + width * y;
    for (int i = 0; i < shape.size; i++)
    {
        for (int j = 0; j < shape.size; j++)
        {
            if ((i + x - shape.radius) >= 0 && 
                (i + x - shape.radius) < width && 
                (j + y - shape.radius) >= 0 && 
                (j + y - shape.radius) < height &&
                shape.mask[i + j * shape.size])
                if (method(gray_buffer[(i + x - shape.radius) + width * (j + y - shape.radius)], value))
                {
                    value = gray_buffer[(i + x - shape.radius) + width *(j + y - shape.radius)];
                    pos = (i + x - shape.radius) + width *(j + y - shape.radius);
                }
        }
    }

    return pos;
}

uint8_t* get_morpho(uint8_t* src_buffer, uint8_t* gray_buffer, int width, int height, const morpho_shape& shape, bool (*method)(uint8_t buffer_val, uint8_t value))
{
    uint8_t* res_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t) * 3);
    uint8_t* tmp_gray_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t));

    // Morpho
    for (int y = 0; y < height; y++)
    {
        uint8_t* res_lineptr = (res_buffer + y * width * 3);
        uint8_t* tmp_gray_lineptr = (tmp_gray_buffer + y * width);
        for (int x = 0; x < width; x++)
        {
            uint64_t morpho_pos = get_morpho_pos(gray_buffer, x, y, width, height, shape, method);
            res_lineptr[x * 3 + 0] = src_buffer[morpho_pos * 3 + 0];
            res_lineptr[x * 3 + 1] = src_buffer[morpho_pos * 3 + 1];
            res_lineptr[x * 3 + 2] = src_buffer[morpho_pos * 3 + 2];
            tmp_gray_lineptr[x] = gray_buffer[morpho_pos];
        }
    }

    // Deep copy of black and white dilation
    for (int i = 0; i < height * width * sizeof(uint8_t); i++)
        gray_buffer[i] = tmp_gray_buffer[i];

    free(tmp_gray_buffer);
    free(src_buffer);

    return res_buffer;
}