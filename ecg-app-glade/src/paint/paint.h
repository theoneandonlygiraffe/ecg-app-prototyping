#ifndef PAINT_H_
#define PAINT_H_

#include <gtk/gtk.h>
#include <vector>
#include <bits/stdc++.h>

#include "../signal/vector_processing.h"
#include "rect.h"

class pofOrigin{
	private:
		Eigen::Vector2d _offset;
		double _scalex,_scaley;
	public:

		pofOrigin(){_offset(0)=0; _offset (1)=0;_scalex=1;_scaley=1;};
		pofOrigin(double x,double y){_offset(0)=x; _offset (1)=y; _scalex=1;_scaley=1;};

		void operator=(const pofOrigin &in){_offset=in.getoffset();  _scalex=in.getscalex();_scaley=in.getscaley();};

		double getscalex() const {return _scalex;};
		double getscaley() const {return _scaley;};
		Eigen::Vector2d getoffset() const {return _offset;};

		//scale
		void setScale(double s){_scalex=s;_scaley=s;};
		void setScale(double x, double y){_scalex=x;_scaley=y;};

		double scaleX(double x) const {return _scalex*x;};
		double scaleY(double y) const {return _scaley*y;};

		//origin
		void moveto(double x, double y){_offset(0)=x; _offset(1)=y;};
		void moveto(const Eigen::Vector2d &vect){_offset=vect;};

		void paint(cairo_t *cr, const rect& frame);

};

void paintline(cairo_t* cr,double x1,double y1, double x2, double y2);
void paintline(cairo_t* cr, const pofOrigin& origin,Eigen::Vector2d p1,Eigen::Vector2d p2);

int paint_vector(std::vector<double> &v, cairo_t *cr,uint offset_x,uint offset_y,uint width,uint height);

void paintV2d(Eigen::Vector2d vect, cairo_t *cr, double offsetx,double offsety);

#endif //PAINT_H_