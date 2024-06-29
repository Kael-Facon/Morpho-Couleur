#include "disk.hh"
#include <stdint.h>

uint8_t dilation(uint8_t* buffer, int x, int y, int width, int height, int stride)
{
    uint8_t max_value = buffer[x * 3 + stride * y];
    for (int i = 0; i < MORPHO_SIZE; i++)
    {
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            if ((i + x - MORPHO_RADIUS) >= 0 && 
                (i + x - MORPHO_RADIUS) < width && 
                (j + y - MORPHO_RADIUS) >= 0 && 
                (j + y - MORPHO_RADIUS) < height &&
                morpho_disk[i][j])
                if (buffer[(i + x - MORPHO_RADIUS) * 3 + stride * (j + y - MORPHO_RADIUS)] > max_value)
                    max_value = buffer[(i + x - MORPHO_RADIUS) * 3 + stride *(j + y - MORPHO_RADIUS)];
        }
    }

    return max_value;
}

uint8_t erosion(uint8_t* buffer, int x, int y, int width, int height, int stride)
{
    uint8_t min_value = buffer[x * 3 + stride * y];
    for (int i = 0; i < MORPHO_SIZE; i++)
    {
        for (int j = 0; j < MORPHO_SIZE; j++)
        {
            if ((i + x - MORPHO_RADIUS) >= 0 && 
                (i + x - MORPHO_RADIUS) < width && 
                (j + y - MORPHO_RADIUS) >= 0 && 
                (j + y - MORPHO_RADIUS) < height &&
                morpho_disk[i][j])
                if (buffer[(i + x - MORPHO_RADIUS) * 3 + stride * (j + y - MORPHO_RADIUS)] < min_value)
                    min_value = buffer[(i + x - MORPHO_RADIUS) * 3 + stride *(j + y - MORPHO_RADIUS)];
        }
    }

    return min_value;
}

/**
 * @param[in, out] residual_image_buffer
 * @param[in, out] tmp_buffer
 */
void open_morpho(uint8_t* residual_image_buffer, uint8_t* tmp_buffer, int width, int height, int stride)
{
    if (!morpho_disk[MORPHO_RADIUS][MORPHO_RADIUS])
        create_disk();
    
    // Erosion    

    for (int y = 0; y < height; y++)
    {
        rgb* tmp_buffer_lineptr = (rgb*) (tmp_buffer + y * stride);
        for (int x = 0; x < width; x++)
        {
            uint8_t min = erosion(residual_image_buffer, x, y, width, height, stride);
            tmp_buffer_lineptr[x].r = min;
            tmp_buffer_lineptr[x].g = min;
            tmp_buffer_lineptr[x].b = min;
        }
    }

    // Dilation

    for (int y = 0; y < height; y++)
    {
        rgb* residual_image_lineptr = (rgb*) (residual_image_buffer + y * stride);
        for (int x = 0; x < width; x++)
        {
            uint8_t max = dilation(tmp_buffer, x, y, width, height, stride);
            residual_image_lineptr[x].r = max;
            residual_image_lineptr[x].g = max;
            residual_image_lineptr[x].b = max;
        }
    }
}