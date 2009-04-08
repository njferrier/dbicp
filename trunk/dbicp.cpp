#include "dbicp.h"

using namespace cimg_library;

DBICP::DBICP(PointSet ps1, PointSet ps2) {
    this->ps1=ps1;
    this->ps2=ps2;

    unsigned char COLOR_orange[]={ 255,128,64 };
    unsigned char COLOR_blue[]={ 0,0,255 };

    int width=1000,height=1000,depth=1,nb_channels=3;
    CImg<unsigned char> Blackboard(width,height,depth,nb_channels,0);
    ps1.draw_points(Blackboard,COLOR_blue);
    ps2.display(Blackboard,COLOR_orange);






}

