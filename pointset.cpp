#include "pointset.h"

using namespace std;
using namespace cimg_library;

void PointSet::fill_with_random(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
            this->push_back(Point2D(rand()%1000,rand()%1000));
    }
}


void PointSet::display_in_console() const {
    for (unsigned int i=0;i<this->size();i++){
        cout << endl <<"Point #" << i+1 <<endl;
        ((*this)[i]).display_in_console();

    }

}

void PointSet::draw_points(CImg<unsigned char> &img) const {
    const unsigned char color[] = { 255,128,64 };
    int radius = 5;
    for (unsigned int i=0;i<this->size();i++){
        img.draw_circle(((*this)[i]).x,((*this)[i]).y,radius,color);
    }

}

void PointSet::display(CImg<unsigned char> &img) const {
    draw_points(img);
    img.display("Nice PointSet, isn't it?");


}


void PointSet::fill_with_set1(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
            this->push_back(Point2D(100+30*cos(i),20+30*i));
    }
}
