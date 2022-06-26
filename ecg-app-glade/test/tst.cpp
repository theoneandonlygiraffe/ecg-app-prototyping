#include <iostream>
#include <eigen3/Eigen/Eigen>

#include <gtk/gtk.h>
 
//using Eigen::MatrixXd;

#define PI 3.14159265



Eigen::Vector2d v2dfromPolar(double r,double th){
	Eigen::Vector2d vect;
	
	vect(0)=r*cos(th * PI / 180.0);
	vect(1)=r*sin(th * PI / 180.0);

	return vect;
}
 
int main()
{
	Rectangle rect(0,0,100,100);


}
