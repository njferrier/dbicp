#ifndef Point2D_H
#define Point2D_H

#include <iostream>

class Point2D {
    public:
        double x, y;

        Point2D();
        Point2D(double x, double y);
        ~Point2D();
        double get_dist_with(Point2D &other);
        double get_sd_with(Point2D &other);
        void display() const;




};

#endif
