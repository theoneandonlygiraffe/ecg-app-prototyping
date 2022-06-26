#ifndef VECTOR_PROCESSING_H_
#define VECTOR_PROCESSING_H_

#include <vector>
#include <bits/stdc++.h>
#include <math.h>

#include "filt.h"
#include <eigen3/Eigen/Eigen>
#include "../paint/rect.h"



#define PI 3.14159265


double mapValue(double a0, double a1, double b0, double b1, double a);

rect getFramefromv2ds(std::vector<Eigen::Vector2d> array);

std::vector<double> deriveVector(const std::vector<double> &v,int h);

std::vector<double> filterVector(const std::vector<double> &v,int tabs,int samplingfreq,int filterfreq);

Eigen::Vector2d v2dfromPolar(double r,double th);
Eigen::Vector2d v2dfromPolar(double th);


#endif //VECTOR_PROCESSING_H_