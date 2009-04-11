#ifndef Point2D_H
#define Point2D_H

#include <iostream>

class Point2D {
    public:
        double x, y;

        Point2D();
        Point2D(double x, double y);
        double get_dist_with(const Point2D &other) const;
        double get_sd_with(const Point2D &other) const;
        void display_in_console() const;




};

#endif
