#ifndef TRANSFO_H
#define TRANSFO_H

#include "Point2D.h"


class Transfo {
public:

    double t11, t12, t13, t14, t15, t16, t21, t22, t23, t24, t25, t26;

    Transfo();
    Transfo(double t11,double t12, double t13, double t14, double t15, double t16,double t21,double t22, double t23, double t24, double t25, double t26);
    Transfo(double t11,double t12, double t13, double t21,double t22, double t23);
    ~Transfo();
    void display();




    Point2D operator()(Point2D point);





};



#endif
