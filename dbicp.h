#ifndef DBICP_H
#define DBICP_H

#define INF 100000000
#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1
#define NB_CHANNELS 3

#include "CImg.h"
#include "pointset.h"
#include <vector>

using namespace cimg_library;
using namespace std;

class DBICP {
public:
    DBICP(PointSet ps1, PointSet ps2);

private:
    CImg<unsigned char> Blackboard;

    PointSet ps1;
    PointSet ps2;
    PointSet tmp;
    vector<int> corres;
    double error;
    void perform_matching_step();
    void perform_optim_step();
    void compute_corres();
    void draw_corres();
    void compute_n_draw_corres();




};



#endif
