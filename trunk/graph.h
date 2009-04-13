#ifndef GRAPH_H
#define GRAPH_H

#include "CImg.h"
#include <vector>
#include <iostream>
#include "tools.h"


using namespace cimg_library;
using namespace std;

class Graph {
public:
    Graph();
    Graph(int dim_x,int dim_y, int point_size=2);
    void assign(int dim_x,int dim_y, int point_size=2);
    void draw(vector<double> values, const unsigned char color[],const char* legend="");
    void clean();
    void display(const char* title="");
    void save(const char* filename="Output/Graph.bmp");

private:
    CImg<unsigned char> graph;
    int dim_x, dim_y,point_size;
    double x_scaling_factor, y_scaling_factor;



};



#endif

