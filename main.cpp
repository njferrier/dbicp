#include <iostream>
#include "transfo.h"
#include "Point2D.h"
#include "similarity.h"
#include "pointset.h"
#include "dbicp.h"


using namespace std;
using namespace cimg_library;

int main() {
    PointSet ps,ps1,ps2;
    Similarity S(50,0.7,0.6,100);

   /* Point2D a(1.5,3.44);
    a.display_in_console();
    cout << endl;

    Transfo T2(2,3,5,2,1,8);
    T2.display();

    cout << endl;
    T2(a).display_in_console();


    S.display();

    cout << endl;

    Point2D b(2,4);
    double d=a.get_dist_with(b);
    cout << endl << d;

    ps.fill_with_random(10);
    ps.display_in_console();
*/


    /**
    * Test with set 1 and S
    **/

    ps1.fill_with_set1(40);
    S(ps1,ps2);

/*    cout << endl <<"PS1" << endl;
    ps1.display_in_console();

    cout << endl <<"PS2" << endl;
    ps2.display_in_console();

*/
    DBICP yeah(ps1,ps2);




    return 0;

}
