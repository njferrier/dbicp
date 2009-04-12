#include <iostream>
#include "transfo.h"
#include "Point2D.h"
#include "similarity.h"
#include "pointset.h"
#include "dbicp.h"


using namespace std;
using namespace cimg_library;

int main() {
    cout << "=====================================================" << endl
         << "          Welcome in DBICP demo program" << endl
         << "=====================================================" << endl << endl;

    PointSet ps,ps1,ps2;
    Similarity S(250,0.7,0.6,200);
    cout << "Similarity used to move points:" << endl;
    S.display();

    /**
    * Test with set 1 and S
    **/

    ps1.fill_with_set1(40);
    S(ps1,ps2);

    DBICP yeah(ps1,ps2);
    yeah.perform();

    cout << "=====================================================" << endl
         << "     That's the end folks, I hope you enjoyed it!" << endl
         << "=====================================================" << endl << endl;


    return 0;

}
