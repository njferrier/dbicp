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
    cout << "BoundingBox[x_min,y_min,x_max,y_max] : ["<<x_min<<", "<<y_min<<", "<<x_max<<", "<<y_max<<"]"<<endl<<endl;
}

void BoundingBox::expand_in_all_dir(double growth){
    x_min -= growth;
    y_min -= growth;
    x_max += growth;
    y_max += growth;
}

void BoundingBox::expand_in_all_dir(double growth, double xmin, double ymin, double xmax, double ymax){

    if (x_min != max(x_min-growth,xmin) || y_min != max(y_min-growth,ymin) || x_max != min(x_max+growth,xmax) || y_max != min(y_max+growth,ymax)) {
        cout << "Bootstrap region resized:" << endl;
        display();
    }

    x_min = max(x_min-growth,xmin);
    y_min = max(y_min-growth,ymin);
    x_max = min(x_max+growth,xmax);
    y_max = min(y_max+growth,ymax);
}
