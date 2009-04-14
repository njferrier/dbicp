#include "dbicp.h"

#define INF 100000000

// Constants for Blackboard
#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1
#define NB_CHANNELS 3

// Constants for gradient descent
#define RHO_0 1e-8
#define RHO_1 1e-8
#define EPSILON_0 1e-3
#define EPSILON_1 1e-3
#define GD_NITER_MAX 100

// Constant for Beaton Tukey
#define BT_A 1e7

// Constant for DBICP
#define DBICP_NITER_MAX 200

// Constant for display
#define TEMPORARY_DISPLAY_TIME 10

// Constant for saving
#define SAVE true

// Constants for Step By Step
#define STEP_BY_STEP true
#define SAVE_STEPS false
#define SAVE_VID false

// Constant for Initial transfo
#define INIT_WITH_BARY_TRANSL false

// Constants for Region Bootstrapping
#define REGION_GROWTH 30
#define RB_THRESHOLD 1e2
#define INIT_BR_AROUND_BEST_MATCH true
#define BR_INIT_SIZE 30

using namespace cimg_library;
using namespace std;


/*****************************************
*            CONSTRUCTOR                 *
******************************************/

DBICP::DBICP(PointSet ps1, PointSet ps2) {
    this->ps1=ps1;
    this->ps2=ps2;

    corres.resize(ps1.size());
    ps1_img.resize(ps1.size());
    ps2_NN2img.resize(ps1.size());
    box_mask.resize(ps1.size());

    costs.resize(DBICP_NITER_MAX);
    cost_graph.assign(1000,1000);

    transfo=Transfo();

    if (INIT_WITH_BARY_TRANSL) {
        // Initialize with mean translation instead of identity
        transfo.t11 = ps2.get_x_mean()-ps1.get_x_mean();
        transfo.t21 = ps2.get_y_mean()-ps1.get_y_mean();
    }

    //transfo.t11 = 250;
    //transfo.t21 = 200;

    transfo(ps1,ps1_img);

    Blackboard.assign(WIDTH,HEIGHT,DEPTH,NB_CHANNELS);

    if (INIT_BR_AROUND_BEST_MATCH) {
        double dummy;
        int min_ind;
        ps1_img.min_wrt_dist(ps2, dummy, min_ind);
        double x_init=ps1[min_ind].x,y_init=ps1[min_ind].y;

        box.assign(max(0.0,x_init-BR_INIT_SIZE/2),max(0.0,y_init-BR_INIT_SIZE/2),min(double(WIDTH),x_init+BR_INIT_SIZE/2),min(double(HEIGHT),y_init+BR_INIT_SIZE/2));
    } else {
        box.assign(0,0,1000,900);
    }

    cout << "Initial Bootstrap Region:" << endl;
    box.display();

    ps1.is_in_bounding_box(box,box_mask);

    cout << "Initial transformation:"<< endl;
    transfo.display();
}



/*****************************************
*            GENERAL ALGORITHM           *
******************************************/

void DBICP::perform() {
    cout << "Performing DBICP..." << endl<< endl;

    CImgList<unsigned char> steps;

    for (unsigned int i=0;i<DBICP_NITER_MAX;i++){
        perform_matching_step(); step_stuff(steps,"Matching",i);
        perform_optim_step(); step_stuff(steps,"Optim",i);
        bootstrap_region(i);
        costs[i]=cost(transfo);

    }

    cout << "Estimated transformation:" << endl;
    transfo.display();

    if (STEP_BY_STEP && SAVE_VID) {
        cout << "Saving video... ";
        const unsigned int fps=1;
        string filename = "Output/Basic ICP - "+to_string(GD_NITER_MAX)+" GD iter - "+to_string(DBICP_NITER_MAX)+" DBCIP iter.mpg";
        steps.save_ffmpeg(filename.c_str(),0,steps.size-1,fps);
        cout << "Done." << endl << endl;
    }


    display(string("Final result"));

    unsigned char COLOR_red[]={255,0,0};
    cost_graph.draw(costs,COLOR_red,"Error cost");
    cost_graph.display("Error Cost");

    Graph approx_err_der(1000,1000);

    vector<double> approx_err_der_values;
    approx_err_der_values.resize(costs.size());
    for (unsigned int i=0; i<costs.size()-1;i++)
        approx_err_der_values[i] = costs[i+1]-costs[i];

    approx_err_der.draw(approx_err_der_values,COLOR_red,"dE/dt");
    approx_err_der.display("dE/dt");

    if (SAVE) {
        string filename="Output/Basic ICP - "+to_string(GD_NITER_MAX)+" GD iter - "+to_string(DBICP_NITER_MAX)+" DBCIP iter.jpg";
        Blackboard.save(filename.c_str());
        filename="Output/Cost Graph - Basic ICP - "+to_string(GD_NITER_MAX)+" GD iter - "+to_string(DBICP_NITER_MAX)+" DBCIP iter.jpg";
        cost_graph.save(filename.c_str());
        //filename="Output/Approx Cost Derivative Graph - Basic ICP - "+to_string(GD_NITER_MAX)+" GD iter - "+to_string(DBICP_NITER_MAX)+" DBCIP iter.jpg";
        //approx_err_der.save(filename.c_str());


    }

}


/*****************************************
*       FUNCTIONS FOR STEP BY STEP       *
******************************************/
void DBICP::step_stuff(CImgList<unsigned char> &steps,string step_name,int iter_nb) {
    if (STEP_BY_STEP) {
        string legend="Iteration #"+to_string(iter_nb+1)+" - "+step_name+" step";
        display(legend,true);
        if (SAVE_STEPS) {
            string filename="Output/Step by Step/Basic ICP - Iteration #"+to_string(iter_nb+1)+" - "+step_name+" step.jpg";
            Blackboard.save(filename.c_str());
        }
        if (SAVE_VID){
            steps.insert(Blackboard);
            if (iter_nb<5) {
                for (unsigned int fps_patch=0;fps_patch<2;fps_patch++) // Extra pictures at the beginning
                    steps.insert(Blackboard);
            }
        }
    }
}

/*****************************************
*           MATCHING FUNCTIONS           *
******************************************/
void DBICP::perform_matching_step(){
    // Updates images
    transfo(ps1,ps1_img,box_mask);
    // Compute correspondances
    compute_corres();

}

void DBICP::compute_corres(bool all_points) {
    /**
    * Compute correspondances (update corres and ps2_NN2img) for the point in the Bounding Box (except if all_points is true).
    */

    for (unsigned int i=0;i<ps1.size();i++) {
        if (box_mask[i] or all_points) {
            double error_i_min = INF;

            for (unsigned int j=0;j<ps2.size();j++) {
                if (ps1_img[i].get_dist_with(ps2[j])<error_i_min) {
                    error_i_min = ps1_img[i].get_dist_with(ps2[j]);
                    corres[i]=j;
                    ps2_NN2img[i]=ps2[j];
                }
            }
        }
    }

}



/*****************************************
*      OPTIMISATION FUNCTIONS            *
******************************************/

void DBICP::perform_optim_step() {
    // We use only similarity for now
    Similarity S=get_optimal_similarity();
    transfo=S;
}

Similarity DBICP::get_optimal_similarity() {
    return get_optimal_similarity_using_gd();
}

Similarity DBICP::get_optimal_similarity_using_gd() {
    /**
    * Get the optimal similarity using gradient descent.
    * It uses the cost function DBICP::cost
    * The number of iterations if GD_NITER_MAX
    */

    Similarity S(transfo.t11,transfo.t12,transfo.t13,transfo.t21);

    for (unsigned int i=0;i<GD_NITER_MAX;i++){
        S.t11 -= RHO_0*(cost(Similarity(S.t11+EPSILON_0,S.t12,S.t13,S.t21))-cost(S))/EPSILON_0;
        S.t12 -= RHO_1*(cost(Similarity(S.t11,S.t12+EPSILON_1,S.t13,S.t21))-cost(S))/EPSILON_1;
        S.t13 -= RHO_1*(cost(Similarity(S.t11,S.t12,S.t13+EPSILON_1,S.t21))-cost(S))/EPSILON_1;
        S.t21 -= RHO_0*(cost(Similarity(S.t11,S.t12,S.t13,S.t21+EPSILON_0))-cost(S))/EPSILON_0;

        S.assign(S.t11,S.t12,S.t13,S.t21);
    }

    return S;

}

double DBICP::cost(const Transfo &T) {
    /**
    * Cost function a given transformation, for the points in the Bounding Box
    */
    T(ps1,ps1_img,box_mask); // Just to be sure the image points are computed

    return Beaton_Tukey_rho(ps1_img.get_dist_with(ps2_NN2img,box_mask));
}

double DBICP::Beaton_Tukey_rho(const double &u) const {
    /**
    * Beaton Tukey function
    */
    if (abs(u)>BT_A){
        return BT_A*BT_A/6;
    } else {
        return BT_A*BT_A/6*(1-pow(1-pow(u/BT_A,2),3));
    }
}




/*****************************************
*           BOOTSTRAP FUNCTIONS          *
******************************************/

void DBICP::bootstrap_region(int iter_nb) {
    if (iter_nb>0) {
        cout << costs[iter_nb-1]-costs[iter_nb] << endl;
        if (costs[iter_nb-1]-costs[iter_nb] < RB_THRESHOLD) {
            box.expand_in_all_dir(REGION_GROWTH,0,0,HEIGHT,WIDTH);
            cout << "New bootstrap region:" << endl;
            box.display();
        }
    }
}





/*****************************************
*           DISPLAY FUNCTIONS            *
******************************************/


void DBICP::draw_corres(const unsigned char color1[],const unsigned char color2[]) {
    /**
    * This function draw arrows on the blackboard, from ps1 to ps1_img, and from ps1_img to ps2_NN2img.
    * Color1 within the bounding box, Color2 without
    */

    for (unsigned int i=0; i<ps1.size();i++){
        if (box_mask[i]) {
            Blackboard.draw_arrow(arrow_p(ps1[i].x),arrow_p(ps1[i].y),arrow_p(ps1_img[i].x),arrow_p(ps1_img[i].y),color1,.5,30,8);
            Blackboard.draw_arrow(arrow_p(ps1_img[i].x),arrow_p(ps1_img[i].y),arrow_p(ps2_NN2img[i].x),arrow_p(ps2_NN2img[i].y),color1,.5,30,8);
        }
        else {
            Blackboard.draw_arrow(arrow_p(ps1[i].x),arrow_p(ps1[i].y),arrow_p(ps1_img[i].x),arrow_p(ps1_img[i].y),color2,.5,8,5);
            Blackboard.draw_arrow(arrow_p(ps1_img[i].x),arrow_p(ps1_img[i].y),arrow_p(ps2_NN2img[i].x),arrow_p(ps2_NN2img[i].y),color2,.5,8,5);
        }
    }
}

void DBICP::display(string legend, bool temporary) {

    // Update everything for ALL the points (not only the one in the bounding box)
    transfo(ps1,ps1_img);
    compute_corres(true);

    Blackboard.fill(0); // Clean the blackboard!

    unsigned char COLOR_orange[]={248,90,4}, COLOR_blue[]={0,0,255}, COLOR_green[]={0,255,0}, COLOR_red[]={255,0,0}, COLOR_purple[]={140,7,131}, COLOR_dark_blue[]={0,0,130}, COLOR_yellow[]={255,255,0},COLOR_black[]={0,0,0};

    ps1.draw_points(Blackboard,COLOR_green);
    ps2.draw_points(Blackboard,COLOR_red);
    ps1_img.draw_points(Blackboard,COLOR_yellow);

    draw_corres(COLOR_blue,COLOR_dark_blue);

    box.draw(Blackboard,COLOR_purple);

    const int font_size = 35;

    Blackboard.draw_text(400,30,legend.c_str(),COLOR_orange,COLOR_black,1,font_size);

    Blackboard_disp << Blackboard;
    Blackboard_disp.show();

    if (!temporary) {
        while (!Blackboard_disp.is_closed){
            usleep(1e3);
        }
    }
    else {
        usleep(TEMPORARY_DISPLAY_TIME);
    }





}



