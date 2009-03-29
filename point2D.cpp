#include "Point2D.h"
#include <math.h>

using namespace std;

Point2D::Point2D(){

    this->x = 0;
    this->y = 0;
}

Point2D::Point2D(double x, double y){
    this->x = x;
    this->y = y;

}

Point2D::~Point2D(){
}

void Point2D::display(){
    cout << x << endl << y << endl;

}

double Point2D::get_dist_with(Point2D &other){
    return sqrt(pow(x-other.x,2)+pow(y-other.y,2));
}
