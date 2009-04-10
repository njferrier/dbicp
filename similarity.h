#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "transfo.h"
#include "point2D.h"
#include "pointset.h"


class Similarity : public Transfo{
public:
    Similarity();
    Similarity(double t11, double t12, double t13, double t21);
    Point2D operator()(const Point2D &point) const ;
    void operator()(const Point2D &point,Point2D &result) const ;
    void operator()(const PointSet &ps,PointSet &result) const;


};



#endif
