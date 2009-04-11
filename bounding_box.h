#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "CImg.h"

using namespace cimg_library;

class BoundingBox {
    public:
        double x_min;
        double x_max;
        double y_min;
        double y_max;

        BoundingBox();
        BoundingBox(double x_min, double y_min, double x_max, double y_max);

        void assign(double x_min, double y_min, double x_max, double y_max);

        void draw(CImg<unsigned char> &pic, const unsigned char color[]);




};



#endif

