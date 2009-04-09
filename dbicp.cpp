#include "dbicp.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

DBICP::DBICP(PointSet ps1, PointSet ps2) {
    this->ps1=ps1;
    this->ps2=ps2;
    this->corres.resize(ps1.size());
    this->error=0;

    Blackboard.assign(WIDTH,HEIGHT,DEPTH,NB_CHANNELS);


    unsigned char COLOR_orange[]={ 255,128,64 };
    unsigned char COLOR_blue[]={ 0,0,255 };

    ps1.draw_points(Blackboard,COLOR_blue);
    ps2.draw_points(Blackboard,COLOR_orange);
    compute_n_draw_corres();
    Blackboard.display("Nice correspondances, right?");


}

void DBICP::compute_corres() {
    error=0;

    for (unsigned int i=0;i<ps1.size();i++) {
        double error_i_min = INF;

        for (unsigned int j=0;j<ps2.size();j++) {
            if (ps1[i].get_dist_with(ps2[j])<error_i_min) {
                error_i_min = ps1[i].get_dist_with(ps2[j]);
                corres[i]=j;
            }
        }
        error+=error_i_min;
    }

}

void DBICP::draw_corres() {
    unsigned char COLOR_green[] = {0,255,0};
    for (unsigned int i=0; i<ps1.size();i++){
        Blackboard.draw_arrow(ps1[i].x,ps1[i].y,ps2[corres[i]].x,ps2[corres[i]].y,COLOR_green);
    }
}

void DBICP::compute_n_draw_corres() {
    compute_corres();
    draw_corres();

}
