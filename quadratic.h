#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "transfo.h"
#include "point2D.h"
#include "pointset.h"


class Quadratic : public Transfo{
public:
    Quadratic();
    Quadratic(double t11,double t12, double t13, double t14, double t15, double t16,double t21,double t22, double t23, double t24, double t25, double t26);

};



#endif

