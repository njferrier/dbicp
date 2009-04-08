#include <iostream>
#include "transfo.h"
#include "Point2D.h"
#include "similarity.h"
#include "pointset.h"
#include "dbicp.h"

using namespace std;
using namespace cimg_library;

int main() {
    Point2D a(1.5,3.44);
    a.display_in_console();
    cout << endl;

    Transfo T2(2,3,5,2,1,8);
    T2.display();

    cout << endl;
    T2(a).display_in_console();

    Similarity S(1,2,3,4);
    S.display();

    cout << endl;

    Point2D b(2,4);
    double d=a.get_dist_with(b);
    cout << endl << d;

    PointSet ps,ps1;
    ps.fill_with_random(10);
    ps.display_in_console();

    ps1.fill_with_set1(40);




    DBICP yeah(ps1,ps1);




    return 0;

}
