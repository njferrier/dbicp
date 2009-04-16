#ifndef DBICP_H
#define DBICP_H

#include "CImg.h"
#include "pointset.h"
#include <vector>
#include "transfo.h"
#include "similarity.h"
#include "quadratic.h"
#include "bounding_box.h"
#include "tools.h"
#include "cimg_patch.h"
#include "graph.h"


using namespace cimg_library;
using namespace std;

class DBICP {
public:
    DBICP(PointSet ps1, PointSet ps2);
    void perform();

private:
    CImg<unsigned char> Blackboard;
    CImgDisplay Blackboard_disp;
    BoundingBox box;
    Graph cost_graph;

    PointSet ps1,ps2,ps1_img,ps2_NN2img;
    // ps1_img: ps1 tranformed
    // ps2_NN2img: ps2[i] is the nearest neighbor of ps1[i] in ps2

    vector<int> corres;
    vector<bool> box_mask;

    Transfo transfo;

    vector<double> costs;

    void perform_matching_step();
    void perform_optim_step(string &transfo_name, bool quadratic_enabled);
    void step_stuff(CImgList<unsigned char> &steps,string step_name, string transfo_name, int iter_nb);

    void bootstrap_region(int iter_nb);

    void compute_corres(bool all_points=false);
    void draw_corres(const unsigned char color1[],const unsigned char color2[]);

    double cost(const Transfo &T);

    double Beaton_Tukey_rho(const double &u) const;

    Similarity get_optimal_similarity();
    Similarity get_optimal_similarity_using_gd();
    Quadratic get_optimal_quadratic();
    Quadratic get_optimal_quadratic_using_gd();

    void display(string legend="",string legend2="",bool temporary=false);




};



#endif
