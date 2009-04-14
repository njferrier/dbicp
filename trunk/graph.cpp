#include "graph.h"

using namespace std;

Graph::Graph(){}

Graph::Graph(int dim_x,int dim_y, int point_size){
    this->dim_x = dim_x;
    this->dim_y = dim_y;
    this->point_size = point_size;

    graph.assign(dim_x,dim_y,1,3);
    graph.fill(255); // White background

}

void Graph::assign(int dim_x,int dim_y, int point_size){
    this->dim_x = dim_x;
    this->dim_y = dim_y;
    this->point_size = point_size;

    graph.assign(dim_x,dim_y,1,3);
    graph.fill(255); // White background

}

void Graph::draw(vector<double> values, const unsigned char color[],const char* legend){
    double x_scaling_factor = dim_x/values.size();

    double max=0;
    double min=INFINITY;

    for (unsigned int i=0;i<values.size();i++){
        if (values[i]<min)
            min = values[i];
    }


    for (unsigned int i=0;i<values.size();i++){
        if (values[i]>max)
            max = values[i];
        values[i]-=min;
    }



    double y_scaling_factor = dim_y/(max-min);


    for (unsigned int i=0; i<values.size();i++) {
        graph.draw_circle(i*x_scaling_factor,dim_y-values[i]*y_scaling_factor,point_size,color);
        if (i>0)
            graph.draw_line((i-1)*x_scaling_factor,dim_y-values[i-1]*y_scaling_factor,i*x_scaling_factor,dim_y-values[i]*y_scaling_factor,color);
    }


    const unsigned char COLOR_white[] = {255,255,255};
    const int font_size = 45;

    string s_min = "Min: " + to_string(min);
    string s_max = "Max: " + to_string(max);

    graph.draw_text(400,20,legend,color,COLOR_white,1,60);
    graph.draw_text(500,90,s_max.c_str(),color,COLOR_white,1,font_size);
    graph.draw_text(500,150,s_min.c_str(),color,COLOR_white,1,font_size);




}


void Graph::clean(){
    graph.fill(255);
}

void Graph::display(const char* title){
    graph.display(title);
}

void Graph::save(const char* filename){
    graph.save(filename);
}


