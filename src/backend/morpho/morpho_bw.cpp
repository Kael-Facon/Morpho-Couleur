#include <stdint.h>

#include "morpho_bw.hh"
#include "../shapes/shape.hh"

uint8_t dilation(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape)
{
    uint8_t max_value = gray_buffer[x + width * y];
    for (int i = 0; i < shape.size; i++)
    {
        for (int j = 0; j < shape.size; j++)
        {
            if ((i + x - shape.radius) >= 0 && 
                (i + x - shape.radius) < width && 
                (j + y - shape.radius) >= 0 && 
                (j + y - shape.radius) < height &&
                shape.mask[i + j * shape.size])
                if (gray_buffer[(i + x - shape.radius) + width * (j + y - shape.radius)] > max_value)
                    max_value = gray_buffer[(i + x - shape.radius) + width *(j + y - shape.radius)];
        }
    }

    return max_value;
}

uint8_t erosion(uint8_t* gray_buffer, int x, int y, int width, int height, const morpho_shape& shape)
{
    uint8_t min_value = gray_buffer[x + width * y];
    for (int i = 0; i < shape.size; i++)
    {
        for (int j = 0; j < shape.size; j++)
        {
            if ((i + x - shape.radius) >= 0 && 
                (i + x - shape.radius) < width && 
                (j + y - shape.radius) >= 0 && 
                (j + y - shape.radius) < height &&
                shape.mask[i + j * shape.size])
                if (gray_buffer[(i + x - shape.radius) + width * (j + y - shape.radius)] < min_value)
                    min_value = gray_buffer[(i + x - shape.radius) + width *(j + y - shape.radius)];
        }
    }

    return min_value;
}

uint8_t* open_morpho(const Image& img, const morpho_shape& shape)
{
    uint8_t* tmp_buffer = (uint8_t*) malloc(img.width * img.height);
    uint8_t* res_buffer = img.get_gray();
    
    // Erosion
    for (int y = 0; y < img.height; y++)
    {
        uint8_t* tmp_buffer_lineptr = (tmp_buffer + y * img.width);
        for (int x = 0; x < img.width; x++)
        {
            uint8_t min = erosion(res_buffer, x, y, img.width, img.height, shape);
            tmp_buffer_lineptr[x + 0] = min;
            tmp_buffer_lineptr[x + 1] = min;
            tmp_buffer_lineptr[x + 2] = min;
        }
    }

    // Dilation
    for (int y = 0; y < img.height; y++)
    {
        uint8_t* res_buffer_lineptr = (res_buffer + y * img.width);
        for (int x = 0; x < img.width; x++)
        {
            uint8_t max = dilation(tmp_buffer, x, y, img.width, img.height, shape);
            res_buffer_lineptr[x + 0] = max;
            res_buffer_lineptr[x + 1] = max;
            res_buffer_lineptr[x + 2] = max;
        }
    }

    return res_buffer;
}

uint8_t* close_morpho(const Image& img, const morpho_shape& shape)
{
    uint8_t* tmp_buffer = (uint8_t*) malloc(img.width * img.height);
    uint8_t* res_buffer = img.get_gray();
    
    // Dilation
    for (int y = 0; y < img.height; y++)
    {
        uint8_t* tmp_buffer_lineptr = (tmp_buffer + y * img.width);
        for (int x = 0; x < img.width; x++)
        {
            uint8_t max = dilation(res_buffer, x, y, img.width, img.height, shape);
            tmp_buffer_lineptr[x + 0] = max;
            tmp_buffer_lineptr[x + 1] = max;
            tmp_buffer_lineptr[x + 2] = max;
        }
    }

    // Erosion
    for (int y = 0; y < img.height; y++)
    {
        uint8_t* res_buffer_lineptr = (res_buffer + y * img.width);
        for (int x = 0; x < img.width; x++)
        {
            uint8_t min = erosion(tmp_buffer, x, y, img.width, img.height, shape);
            res_buffer_lineptr[x + 0] = min;
            res_buffer_lineptr[x + 1] = min;
            res_buffer_lineptr[x + 2] = min;
        }
    }

    return res_buffer;
}