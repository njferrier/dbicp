#include <iostream>
#include "transfo.h"
#include "Point2D.h"
#include "similarity.h"
#include "quadratic.h"
#include "pointset.h"
#include "dbicp.h"
#include "CImg.h"


using namespace std;
using namespace cimg_library;

int main() {
    cout << "=====================================================" << endl
         << "          Welcome in DBICP demo program" << endl
         << "=====================================================" << endl << endl;

    PointSet ps,ps1,ps2;

/*
    Similarity S(250,0.7,0.6,200);
    cout << "Similarity used to move points:" << endl;
    S.display();
*/

    cout << "Quadratic used to move points:" << endl;
  //  Quadratic Q(450,    0.5,    0.4,    1e-4,  -1e-4,  -5e-4,
  //              100,    -.4,    .5,     1e-4,  1e-4,  4e-4);

    Quadratic Q(250,    0.6,    0.7,    -1.4e-3,  -1e-5,1e-5,
                200,    -.7,    .6,     -1e-3,  -1e-3,1e-4);

    Q.display();



    /**
    * Test with set 1 and S
    **/

    ps1.fill_with_set1(40);
    Q(ps1,ps2);

    DBICP yeah(ps1,ps2);
    yeah.perform();

    cout << "=====================================================" << endl
         << "     That's the end folks, I hope you enjoyed it!" << endl
         << "=====================================================" << endl << endl;


    return 0;

}
