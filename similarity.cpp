#include "similarity.h"

using namespace std;

Similarity::Similarity() : Transfo() { }

Similarity::Similarity(double t11, double t12, double t13, double t21) : Transfo(t11,t12,t13,t21,-t13,t12) { }

void Similarity::assign(double t11, double t12, double t13, double t21) {
    this->t11=t11;
    this->t12=t12;
    this->t13=t13;
    this->t21=t21;
    this->t22=-t13;
    this->t23=t12;
 }

Point2D Similarity::operator()(const Point2D &point) const {
    return Point2D(t11 + point.x*t12 + point.y*t13,
                   t21 + point.x*t22 + point.y*t23);
}

void Similarity::operator()(const Point2D &point,Point2D &result) const {
    result.x = t11 + point.x*t12 + point.y*t13;
    result.y = t21 + point.x*t22 + point.y*t23;
}

void Similarity::operator()(const PointSet &ps,PointSet &result) const {
    result.resize(ps.size());
    for (unsigned int i=0;i<ps.size();i++){
        this->operator()(ps[i],result[i]);
    }
}
