#ifndef DBICP_H
#define DBICP_H

#include "CImg.h"
#include "pointset.h"

using namespace cimg_library;

class DBICP {
public:
    CImg<unsigned char> Blackboard;
    PointSet ps1;
    PointSet ps2;
    PointSet tmp;
    DBICP(PointSet ps1, PointSet ps2);

private:
    void perform_matching_step();
    void perform_optim_step();




};



#endif
