#ifndef POINTSET_H
#define POINTSET_H

#include <vector>
#include "point2D.h"
#include "CImg.h"

using namespace cimg_library;

class PointSet : public std::vector<Point2D> {
public:
    void fill_with_random(int nb_points);
    void fill_with_set1(int nb_points);
    void display_in_console() const;
    void draw_points(CImg<unsigned char> &img) const;
    void display(CImg<unsigned char> &img) const;



};



#endif

