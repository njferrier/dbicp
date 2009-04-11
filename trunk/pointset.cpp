#include "pointset.h"

using namespace std;
using namespace cimg_library;


/*****************************************
*           DISPLAY FUNCTIONS            *
******************************************/

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


/*****************************************
*           DISTANCE FUNCTIONS           *
******************************************/


double PointSet::get_dist_with(const PointSet &other) const {
    /**
    * Simple sum of the distances
    */
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

double PointSet::get_dist_with(const PointSet &other,const vector<bool> &mask) const {
    /**
    * Sum of the distances where the value of the mask is true
    */
    double dist=0;
    if (this->size()==other.size() && this->size()==mask.size()) {
        for (unsigned int i=0;i<this->size();i++) {
            if (mask[i])
                dist += (*this)[i].get_dist_with(other[i]);
        }
    }
    else {
        cout << "ERROR in PointSet: point set 1 and 2 and mask must have the same sizes!" <<endl;
        exit(2);
    }
    return dist;
}


/*****************************************
*           FILLING FUNCTIONS            *
******************************************/

void PointSet::fill_with_random(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
        this->push_back(Point2D(rand()%1000,rand()%1000));
    }
}


void PointSet::fill_with_set1(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
        this->push_back(Point2D(100+30*cos(i)*pow(1.02,i),20+22*i));
    }
}


/*****************************************
*             STAT FUNCTIONS             *
******************************************/

double PointSet::get_x_mean(){
    double x_mean = 0;
    for (unsigned int i=0;i<this->size();i++)
        x_mean+=(*this)[i].x;
    x_mean/=this->size();
    return x_mean;
}


double PointSet::get_y_mean(){
    double y_mean = 0;
    for (unsigned int i=0;i<this->size();i++)
        y_mean+=(*this)[i].y;
    y_mean/=this->size();
    return y_mean;
}


/*****************************************
*        BOUNDING BOX FUNCTIONS          *
******************************************/

void PointSet::is_in_bounding_box(const BoundingBox &box,vector<bool> &mask_result) const {
    mask_result.resize(this->size());
    for (unsigned int i=0;i<this->size();i++){
         mask_result[i] = (*this)[i].is_in_bounding_box(box);
    }
}
