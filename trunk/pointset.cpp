#include "pointset.h"

using namespace std;

void PointSet::fill_with_random(int nb_points){
    srand ( time(NULL) );
    for (int i=0;i<nb_points;i++){
            this->push_back(Point2D(rand()%1000,rand()%1000));
    }
}


void PointSet::display() const {
    for (unsigned int i=0;i<this->size();i++){
            cout << endl <<"Point #" << i+1 <<endl;
            ((*this)[i]).display();

    }

}
