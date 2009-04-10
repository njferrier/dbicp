#ifndef DBICP_H
#define DBICP_H

#include "CImg.h"
#include "pointset.h"
#include <vector>
#include "transfo.h"
#include "similarity.h"


using namespace cimg_library;
using namespace std;

class DBICP {
public:
    DBICP(PointSet ps1, PointSet ps2);
    void perform();

private:
    CImg<unsigned char> Blackboard;

    PointSet ps1,ps2,ps1_img,ps2_NN2img;
    // ps1_img: ps1 tranformed
    // ps2_NN2img: ps2[i] is the nearest neighbor of ps1[i] in ps2
    Transfo transfo;

    vector<int> corres;
    double error;
    void perform_matching_step();
    void perform_optim_step();
    void compute_corres();
    void draw_corres(const unsigned char color[]);
    void compute_n_draw_corres(const unsigned char color[]);

    double cost(const Transfo &T);

    double Beaton_Tukey_rho(const double &u) const;

    Similarity get_optimal_similarity();
    Similarity get_optimal_similarity_using_gd();





};



#endif
