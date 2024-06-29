//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#ifndef HISTOGRAM_HH
#define	HISTOGRAM_HH

#include "image.hh"

namespace tifo {

  typedef struct { unsigned int histogram[IMAGE_NB_LEVELS]; } histogram_1d;

    histogram_1d histogrammification(const gray8_image& gray);
    int histo_max(const histogram_1d& histo);
    gray8_image show_histogram(const histogram_1d& histo);
    gray8_image show_histogram(const histogram_1d& histo, int height);
    rgb24_image show_histogram(const rgb24_image& img);

    gray8_image egalize(const gray8_image& img);
    rgb24_image egalize(const rgb24_image& img);
    rgb24_image egalize(const rgb24_image& img);

    gray8_image black_n_white_hsv(const rgb24_image& img);
    rgb24_image egalize_with_hsv(const rgb24_image& img);
    rgb24_image saturate_with_hsv(const rgb24_image& img, float sat);
}

#endif
