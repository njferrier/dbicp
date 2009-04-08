#include "dbicp.h"

using namespace cimg_library;

DBICP::DBICP(PointSet ps1, PointSet ps2) {
    this->ps1=ps1;
    this->ps2=ps2;
    int width=1000,height=1000,depth=1,nb_channels=3;
    CImg<unsigned char> Blackboard(width,height,depth,nb_channels,0);
    ps1.display(Blackboard);






}


