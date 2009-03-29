#include "similarity.h"

Similarity::Similarity(double t11, double t12, double t13, double t21) : Transfo(t11,t12,t13,t21,-t13,t12) { }
