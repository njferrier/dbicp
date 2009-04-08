#ifndef POINTSET_H
#define POINTSET_H

#include <vector>
#include "point2D.h"


class PointSet : public std::vector<Point2D> {
public:
    void fill_with_random(int nb_points);
    void display() const;




};



#endif

