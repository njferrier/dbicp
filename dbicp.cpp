#include "dbicp.h"

#define INF 100000000

// Constants for Blackboard
#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1
#define NB_CHANNELS 3

// Constants for gradient descent
#define RHO 1e-6
#define EPSILON 1e-3
#define GD_NITER_MAX 1000

// Constant for Beaton Tukey
#define BT_A 10000000

// Constant for DBICP
#define DBICP_NITER_MAX 50

using namespace cimg_library;
using namespace std;

DBICP::DBICP(PointSet ps1, PointSet ps2) {
    this->ps1=ps1;
    this->ps2=ps2;
    corres.resize(ps1.size());
    ps1_img.resize(ps1.size());
    ps2_NN2img.resize(ps1.size());
    error=0;
    transfo=Transfo();

    Blackboard.assign(WIDTH,HEIGHT,DEPTH,NB_CHANNELS);

}

void DBICP::perform() {
    unsigned char COLOR_orange[]={ 255,128,64 }, COLOR_blue[]={ 0,0,255 }, COLOR_green[]={ 0,255,0 }, COLOR_red[]={ 255,0,0 };

    Similarity S;

    for (unsigned int i=0;i<DBICP_NITER_MAX;i++){
        compute_corres();
        S=get_optimal_similarity();
        //S.display();
        transfo=S;
    }

    ps1.draw_points(Blackboard,COLOR_green);
    ps2.draw_points(Blackboard,COLOR_red);
    ps1_img.draw_points(Blackboard,COLOR_orange);

    compute_n_draw_corres(COLOR_blue);
    Blackboard.display("Nice correspondances, right?");



}

void DBICP::compute_corres() {
    error=0;

    transfo(ps1,ps1_img);

    for (unsigned int i=0;i<ps1.size();i++) {
        double error_i_min = INF;

        for (unsigned int j=0;j<ps2.size();j++) {
            if (ps1_img[i].get_dist_with(ps2[j])<error_i_min) {
                error_i_min = ps1_img[i].get_dist_with(ps2[j]);
                corres[i]=j;
                ps2_NN2img[i]=ps2[j];
            }
        }
        error+=error_i_min;
    }

}

void DBICP::draw_corres(const unsigned char color[]) {

    for (unsigned int i=0; i<ps1.size();i++){
        Blackboard.draw_arrow(ps1[i].x,ps1[i].y,ps1_img[i].x,ps1_img[i].y,color);
        Blackboard.draw_arrow(ps1_img[i].x,ps1_img[i].y,ps2_NN2img[i].x,ps2_NN2img[i].y,color);
    }
}

void DBICP::compute_n_draw_corres(const unsigned char color[]) {
    compute_corres();
    draw_corres(color);

}

Similarity DBICP::get_optimal_similarity() {
    return get_optimal_similarity_using_gd();
}

Similarity DBICP::get_optimal_similarity_using_gd() {
    /**
    * Get optimal similarity using gradient descent
    */

    Similarity S;

    for (unsigned int i=0;i<GD_NITER_MAX;i++){
        S.t11 -= RHO*(cost(Similarity(S.t11+EPSILON,S.t12,S.t13,S.t21))-cost(S))/EPSILON;
        S.t12 -= RHO*(cost(Similarity(S.t11,S.t12+EPSILON,S.t13,S.t21))-cost(S))/EPSILON;
        S.t13 -= RHO*(cost(Similarity(S.t11,S.t12,S.t13+EPSILON,S.t21))-cost(S))/EPSILON;
        S.t21 -= RHO*(cost(Similarity(S.t11,S.t12,S.t13,S.t21+EPSILON))-cost(S))/EPSILON;
    }

    return S;

}

double DBICP::cost(const Transfo &T) {

    T(ps1,ps1_img);

    return Beaton_Tukey_rho(ps1_img.get_dist_with(ps2_NN2img));
}

double DBICP::Beaton_Tukey_rho(const double &u) const {

    if (abs(u)>BT_A){
        return BT_A*BT_A/6;
    } else {
        return BT_A*BT_A/6*(1-pow(1-pow(u/BT_A,2),3));
    }


}
