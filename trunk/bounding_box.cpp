#include "bounding_box.h"

using namespace std;

BoundingBox::BoundingBox(){
    this->x_min = 0;
    this->x_max = 0;
    this->y_min = 0;
    this->y_max = 0;
}

BoundingBox::BoundingBox(double x_min, double y_min, double x_max, double y_max){
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
}

void BoundingBox::assign(double x_min, double y_min, double x_max, double y_max){
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
}

void BoundingBox::draw(CImg<unsigned char> &pic, const unsigned char color[]){
    pic.draw_line(x_min, y_min, x_min, y_max, color);
    pic.draw_line(x_max, y_min, x_max, y_max, color);
    pic.draw_line(x_min, y_min, x_max, y_min, color);
    pic.draw_line(x_min, y_max, x_max, y_max, color);
}

void BoundingBox::display(){
    cout << "BoundingBox[x_min,y_min,x_max,y_max] : ["<<x_min<<","<<y_min<<","<<x_max<<","<<y_max<<"]"<<endl<<endl;
}
