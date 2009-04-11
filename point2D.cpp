#include "Point2D.h"

using namespace std;

Point2D::Point2D(){
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D(double x, double y){
    this->x = x;
    this->y = y;
}

void Point2D::display_in_console() const {
    cout << x << endl << y << endl;
}

double Point2D::get_dist_with(const Point2D &other) const {
    return sqrt(pow(x-other.x,2)+pow(y-other.y,2));
}



double Point2D::get_sd_with(const Point2D &other) const {
    return pow(x-other.x,2)+pow(y-other.y,2);
}

bool Point2D::is_in_bounding_box(const BoundingBox &box) const {
    if (x>=box.x_min && x<= box.x_max && y>=box.y_min && y<=box.y_max) {
        return true;
    }
    else {
        return false;
    }
}

