#include "similarity.h"

using namespace std;

Similarity::Similarity(double t11, double t12, double t13, double t21) : Transfo(t11,t12,t13,t21,-t13,t12) { }

Point2D Similarity::operator()(Point2D point) const {
    return Point2D(t11 + point.x*t12 + point.y*t13,
                   t21 + point.x*t22 + point.y*t23);
}


void Similarity::get_optimal_similarity(PointSet &ps1, PointSet &ps2, Similarity &s) {
    /*
        ps1:        start points
        ps2:        end points
        similarity: results

    */
    if (ps1.size() == ps2.size()) {

    }
    else {
        cout << "Point sets must have the same number of points!" << endl;
//        error(1);
    }


}
