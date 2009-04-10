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



void PointSet::draw_points(CImg<unsigned char> &img, const unsigned char color[]) const {
    int radius = 5;
    for (unsigned int i=0;i<this->size();i++){
        img.draw_circle((*this)[i].x,(*this)[i].y,radius,color);
    }

}

void PointSet::display(CImg<unsigned char> &img,const unsigned char color[]) const {
    draw_points(img,color);
    img.display("Nice PointSet, isn't it?");


}


void PointSet::fill_with_set1(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
            this->push_back(Point2D(100+30*cos(i),20+30*i));
    }
}

double PointSet::get_dist_with(const PointSet &other) const {
    double dist=0;
    if (this->size()==other.size()) {
        for (unsigned int i=0;i<this->size();i++)
            dist += (*this)[i].get_dist_with(other[i]);
    }
    else {
        cout << "ERROR in PointSet: point sets must have the same sizes!" <<endl;
        exit(2);
    }
    return dist;
}
