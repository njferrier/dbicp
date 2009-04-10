#ifndef TRANSFO_H
#define TRANSFO_H

#include "point2D.h"
#include "pointset.h"

class Transfo {
public:
    double t11, t12, t13, t14, t15, t16, t21, t22, t23, t24, t25, t26;

    Transfo();
    Transfo(double t11,double t12, double t13, double t14, double t15, double t16,double t21,double t22, double t23, double t24, double t25, double t26);
    Transfo(double t11,double t12, double t13, double t21,double t22, double t23);
    ~Transfo();
    void display() const;

    Point2D operator() (const Point2D point) const;
    void operator()(const Point2D &point,Point2D &result) const ;
    void operator()(const PointSet &ps,PointSet &result) const;






};



#endif
