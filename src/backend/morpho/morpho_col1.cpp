#include <stdint.h>

#include "morpho_bw.hh"
#include "../shapes/shape.hh"

uint64_t dilation_col1_(uint8_t* gray_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t max_value = gray_buffer[x + width * y];
    uint64_t max_pos = x + width * y;
    for (int i = 0; i < MORPHO_SIZE; i++)
    {
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            if ((i + x - MORPHO_RADIUS) >= 0 && 
                (i + x - MORPHO_RADIUS) < width && 
                (j + y - MORPHO_RADIUS) >= 0 && 
                (j + y - MORPHO_RADIUS) < height &&
                morpho_shape[i][j])
                if (gray_buffer[(i + x - MORPHO_RADIUS) + width * (j + y - MORPHO_RADIUS)] > max_value)
                {
                    max_value = gray_buffer[(i + x - MORPHO_RADIUS) + width *(j + y - MORPHO_RADIUS)];
                    max_pos = (i + x - MORPHO_RADIUS) + width *(j + y - MORPHO_RADIUS);
                }
        }
    }

    return max_pos;
}

uint8_t* dilation_col1(uint8_t* color_buffer, uint8_t* gray_buffer, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* dilate_color_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t) * 3);
    uint8_t* dilate_gray_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t));

    // Dilation
    for (int y = 0; y < height; y++)
    {
        uint8_t* tmp_color_lineptr = (dilate_color_buffer + y * width * 3);
        uint8_t* tmp_gray_lineptr = (dilate_gray_buffer + y * width);
        for (int x = 0; x < width; x++)
        {
            uint64_t max_pos = dilation_col1_(gray_buffer, x, y, width, height, morpho_shape);
            tmp_color_lineptr[x * 3 + 0] = color_buffer[max_pos * 3 + 0];
            tmp_color_lineptr[x * 3 + 1] = color_buffer[max_pos * 3 + 1];
            tmp_color_lineptr[x * 3 + 2] = color_buffer[max_pos * 3 + 2];
            tmp_gray_lineptr[x] = gray_buffer[max_pos];
        }
    }

    // Deep copy of black and white dilation
    for (int i = 0; i < height * width * sizeof(uint8_t); i++)
        gray_buffer[i] = dilate_gray_buffer[i];

    free(dilate_gray_buffer);
    free(color_buffer);

    return dilate_color_buffer;
}

uint64_t erosion_col1_(uint8_t* gray_buffer, int x, int y, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t min_value = gray_buffer[x + width * y];
    uint64_t min_pos = x + width * y;
    for (int i = 0; i < MORPHO_SIZE; i++)
    {
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            if ((i + x - MORPHO_RADIUS) >= 0 && 
                (i + x - MORPHO_RADIUS) < width && 
                (j + y - MORPHO_RADIUS) >= 0 && 
                (j + y - MORPHO_RADIUS) < height &&
                morpho_shape[i][j])
                if (gray_buffer[(i + x - MORPHO_RADIUS) + width * (j + y - MORPHO_RADIUS)] < min_value)
                {
                    min_value = gray_buffer[(i + x - MORPHO_RADIUS) + width *(j + y - MORPHO_RADIUS)];
                    min_pos = (i + x - MORPHO_RADIUS) + width *(j + y - MORPHO_RADIUS);
                }
        }
    }

    return min_pos;
}

uint8_t* erosion_col1(uint8_t* color_buffer, uint8_t* gray_buffer, int width, int height, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* erode_color_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t) * 3);
    uint8_t* erode_gray_buffer = (uint8_t*) malloc(height * width * sizeof(uint8_t));

    // Erosion
    for (int y = 0; y < height; y++)
    {
        uint8_t* tmp_color_lineptr = (erode_color_buffer + y * width * 3);
        uint8_t* tmp_gray_lineptr = (erode_gray_buffer + y * width);
        for (int x = 0; x < width; x++)
        {
            uint64_t min_pos = erosion_col1_(gray_buffer, x, y, width, height, morpho_shape);
            tmp_color_lineptr[x * 3 + 0] = color_buffer[min_pos * 3 + 0];
            tmp_color_lineptr[x * 3 + 1] = color_buffer[min_pos * 3 + 1];
            tmp_color_lineptr[x * 3 + 2] = color_buffer[min_pos * 3 + 2];
            tmp_gray_lineptr[x] = gray_buffer[min_pos]; 
        }
    }
    
    // Deep copy of black and white erosion
    for (int i = 0; i < height * width * sizeof(uint8_t); i++)
        gray_buffer[i] = erode_gray_buffer[i];

    free(erode_gray_buffer);
    free(color_buffer);

    return erode_color_buffer;
}

uint8_t* open_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Erosion
    color_buffer = erosion_col1(color_buffer, gray_buffer, img.width, img.height, morpho_shape);

    // Dilation
    color_buffer = dilation_col1(color_buffer, gray_buffer, img.width, img.height, morpho_shape);

    return color_buffer;
}

uint8_t* close_morpho_col1(const Image& img, bool morpho_shape[MORPHO_SIZE][MORPHO_SIZE])
{
    uint8_t* gray_buffer = img.get_gray();
    uint8_t* color_buffer = img.get_char_data_copy();

    // Dilation
    color_buffer = dilation_col1(color_buffer, gray_buffer, img.width, img.height, morpho_shape);

    // Erosion
    color_buffer = erosion_col1(color_buffer, gray_buffer, img.width, img.height, morpho_shape);

    return color_buffer;
}