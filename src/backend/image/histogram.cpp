//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#include "histogram.hh"
#include <iostream>
#include <cstring>

namespace tifo
{
    histogram_1d histogrammification(const gray8_image& gray)
    {
        histogram_1d histo;

        for (int i = 0; i < IMAGE_NB_LEVELS; i++)
            histo.histogram[i] = 0;

        for (int i = 0; i < gray.length; i++)
            histo.histogram[gray.pixels[i]]++;
        
        return histo;
    }

    int histo_max(const histogram_1d& histo)
    {
        unsigned int max = histo.histogram[0];
        for (int i = 1; i < IMAGE_NB_LEVELS; i++)
            if (histo.histogram[i] > max)
                max = histo.histogram[i];

        return max;
    }

    gray8_image show_histogram(const histogram_1d& histo) { return show_histogram(histo, 300); }
    gray8_image show_histogram(const histogram_1d& histo, int height)
    {
        int max = histo_max(histo);

        gray8_image img = gray8_image(IMAGE_NB_LEVELS, height);
        std::memset(img.pixels, 0,IMAGE_NB_LEVELS * height);

        for (int i = 0; i < IMAGE_NB_LEVELS; i++)
            for (unsigned int j = 0; j < (histo.histogram[i] * height) / max; j++)
                img.pixels[(j * IMAGE_NB_LEVELS) + i] = IMAGE_MAX_LEVEL;

        return img;
    }

    gray8_image egalize(const gray8_image& img)
    {
        histogram_1d histo = histogrammification(img);

        unsigned int threshold = histo_max(histo) / 10;
        unsigned int bsup = IMAGE_MAX_LEVEL;
        unsigned int binf = 0;

        unsigned int min = binf;
        while (histo.histogram[min] < threshold)
            min++;

        unsigned int max = bsup;
        while (histo.histogram[max] < threshold)
            max--;

        float a = (bsup - binf) / (1.0f * (max - min));

        if (false)
            std::cout << "threshold: " << threshold
                      << ", min: " << min
                      << ", max: " << max
                      << ", a: " << a << std::endl;
        
        gray8_image egalized = gray8_image(img.sx, img.sy);
        for (int i = 0; i < egalized.length; i++)
        {
            unsigned int x = img.pixels[i];

            if (x < min)
                egalized.pixels[i] = binf;
            else if (x > max)
                egalized.pixels[i] = bsup;
            else
                egalized.pixels[i] = (a * x - (min * a));
        }

        return egalized;
    }

    rgb24_image egalize(const rgb24_image& img)
    {
        gray8_image red = egalize(img.get_red_channel());
        gray8_image blue = egalize(img.get_green_channel());
        gray8_image green = egalize(img.get_blue_channel());

        return rgb24_image(red, green, blue);
    }

    rgb24_image show_histogram(const rgb24_image& img)
    {
        gray8_image red = show_histogram(histogrammification(img.get_red_channel()));
        gray8_image blue = show_histogram(histogrammification(img.get_green_channel()));
        gray8_image green = show_histogram(histogrammification(img.get_blue_channel()));

        return rgb24_image(red, green, blue);
    }

    void rgb_to_hsv(rgb24_image *rgb)
    {
        for (int index = 0; index < rgb->length; index += 3)
            convert_hsv(&rgb->pixels[index], 
                        &rgb->pixels[index + 1],
                        &rgb->pixels[index + 2]);        
    }

    void hsv_to_rgb(rgb24_image *hsv)
    {
        for (int index = 0; index < hsv->length; index += 3)
            convert_rgb(&hsv->pixels[index], 
                        &hsv->pixels[index + 1],
                        &hsv->pixels[index + 2]);        
    }

    gray8_image black_n_white_hsv(const rgb24_image& img)
    {
        rgb24_image hsv = rgb24_image(img.get_red_channel(), img.get_green_channel(), img.get_blue_channel());
        rgb_to_hsv(&hsv);

        return hsv.get_channel(2);
    }

    rgb24_image egalize_with_hsv(const rgb24_image& img)
    {
        rgb24_image hsv = rgb24_image(img.get_red_channel(), img.get_green_channel(), img.get_blue_channel());
        rgb_to_hsv(&hsv);

        std::cout << "Egalize value\n"; 
        gray8_image v = egalize(hsv.get_channel(2));

        std::cout << "RGB to HSV\n"; 
        for (int index = 0; index < img.length; index += 3)
            convert_rgb(&hsv.pixels[index],
                        &hsv.pixels[index + 1],
                        //&hsv.pixels[index + 2]);
                        &v.pixels[index / 3]);

        return hsv;
    }

    void multiply(uint8_t *value, float mult)
    {
        float v = (mult * (*value)) / (float) IMAGE_MAX_LEVEL;
        v = v > 1.0 ? 1.0: v;

        *value = (v * IMAGE_MAX_LEVEL);
    }

    rgb24_image saturate_with_hsv(const rgb24_image& img, float sat)
    {
        rgb24_image hsv = rgb24_image(img.get_red_channel(), img.get_green_channel(), img.get_blue_channel());
        rgb_to_hsv(&hsv);

        for (int index = 1; index < hsv.length; index+=3)
            multiply(&(hsv.pixels[index]), sat);

        hsv_to_rgb(&hsv);

        return hsv;
    }
}
