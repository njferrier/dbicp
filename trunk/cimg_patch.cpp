#include "cimg_patch.h"

double arrow_p(double d) {
    // arrow_p is for "arrow protection" or "arrow patch"
    // Because CImg draw_arrow seems to generate segmentation faults with too large values.
    // This use obviously modify the orientations of the arrows which have an extremity far away... but we do not really care!
    if (d<-LARGE_VALUE)
        return -LARGE_VALUE;
    if (d>LARGE_VALUE)
        return LARGE_VALUE;
    return d;
}
