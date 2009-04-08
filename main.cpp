#include <iostream>
#include "transfo.h"
#include "Point2D.h"
#include "similarity.h"
#include "pointset.h"

using namespace std;

int main() {
    Point2D a(1.5,3.44);
    a.display();
    cout << endl;

    Transfo T2(2,3,5,2,1,8);
    T2.display();

    cout << endl;
    T2(a).display();

    Similarity S(1,2,3,4);
    S.display();

    cout << endl;

    Point2D b(2,4);
    double d=a.get_dist_with(b);
    cout << endl << d;

    PointSet ps;
    ps.fill_with_random(10);
    ps.display();



    return 0;

}
