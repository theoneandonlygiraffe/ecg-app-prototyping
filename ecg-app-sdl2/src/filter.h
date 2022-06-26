//https://gist.github.com/agrafix/56592043c43c8801f40ab7667b9e7f0e



#ifndef FILTER_H_
#define FILTER_H_

#include <cmath>
#include <vector>
#include <assert.h>
#include <iostream>




double gauss(double sigma, double x);
std::vector<double> gaussKernel( unsigned int samples, double sigma);
std::vector<double> gaussSmoothen(std::vector<double> values, double sigma, unsigned int samples);


#endif //FILTER_H_