#ifndef POINTSET_H
#define POINTSET_H

#include <vector>
#include "point2D.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

class PointSet : public std::vector<Point2D> {
public:
    void fill_with_random(int nb_points);
    void fill_with_set1(int nb_points);
    void display_in_console() const;
    void draw_points(CImg<unsigned char> &img,const unsigned char color[]) const;
    void display(CImg<unsigned char> &img,const unsigned char color[]) const;
    double get_dist_with(const PointSet &other) const;
    double get_dist_with(const PointSet &other,const vector<bool> &mask) const;
    double get_x_mean();
    double get_y_mean();
    void is_in_bounding_box(const BoundingBox &box,vector<bool> &result) const;
    void min_wrt_dist(const PointSet &other, double &min_dist, int &min_ind) const;



};



#endif

