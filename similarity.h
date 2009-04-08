#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "transfo.h"
#include "point2D.h"
#include "pointset.h"


class Similarity : public Transfo{
public:
    Similarity(double t11, double t12, double t13, double t21);
    Point2D operator()(Point2D &point) const ;
    void operator()(Point2D &point,Point2D &result) const ;
    void operator()(PointSet &ps,PointSet &result) const;
    void get_optimal_similarity(PointSet &ps1, PointSet &ps2, Similarity &s);



};



#endif
