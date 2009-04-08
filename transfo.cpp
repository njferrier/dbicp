#include "transfo.h"

using namespace std;

Transfo::Transfo(){
    this->t11=0;
    this->t12=0;
    this->t13=0;
    this->t14=0;
    this->t15=0;
    this->t16=0;
    this->t21=0;
    this->t22=0;
    this->t23=0;
    this->t24=0;
    this->t25=0;
    this->t26=0;
}

Transfo::Transfo(double t11,double t12, double t13, double t14, double t15, double t16,double t21,double t22, double t23, double t24, double t25, double t26){
    this->t11=t11;
    this->t12=t12;
    this->t13=t13;
    this->t14=t14;
    this->t15=t15;
    this->t16=t16;
    this->t21=t21;
    this->t22=t22;
    this->t23=t23;
    this->t24=t24;
    this->t25=t25;
    this->t26=t26;
}


Transfo::Transfo(double t11,double t12, double t13, double t21,double t22, double t23){
    this->t11=t11;
    this->t12=t12;
    this->t13=t13;
    this->t14=0;
    this->t15=0;
    this->t16=0;
    this->t21=t21;
    this->t22=t22;
    this->t23=t23;
    this->t24=0;
    this->t25=0;
    this->t26=0;
}


Transfo::~Transfo(){
}


void Transfo::display() const {
    cout << t11 << "\t" << t12 << "\t" << t13 << "\t" << t14 << "\t" << t15 << "\t" << t16 << endl << t21 << "\t" << t22 << "\t" << t23 << "\t" << t24 << "\t" << t25 << "\t" << t26 << endl;

}

Point2D Transfo::operator()(Point2D point) const {
    return Point2D(t11 + point.x*t12 + point.y*t13 + point.x*point.x*t14 + point.x*point.y*t15 + point.y*point.y*t16,
                   t21 + point.x*t22 + point.y*t23 + point.x*point.x*t24 + point.x*point.y*t25 + point.y*point.y*t26);
}
