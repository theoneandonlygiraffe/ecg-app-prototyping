#include "paint.h"


void paintline(cairo_t* cr,double x1,double y1, double x2, double y2){
	cairo_move_to(cr,x1,y1);
	cairo_line_to(cr,x2,y2);
	cairo_stroke(cr);
}

void paintline(cairo_t* cr, const pofOrigin& origin,Eigen::Vector2d p1,Eigen::Vector2d p2){
	p1=p1+origin.getoffset();
	p2=p2+origin.getoffset();

	cairo_move_to(cr,p1(0)*origin.getscalex(),p1(1)*origin.getscaley());
	cairo_line_to(cr,p2(0)*origin.getscalex(),p2(1)*origin.getscalex());
	cairo_stroke(cr);
}



int paint_vector(std::vector<double> &v, cairo_t *cr,uint offset_x,uint offset_y,uint width,uint height){

	if(v.empty()){
		//fehler array leer
		return false;
	}
	else
	{
		int step =1;
		uint border=v.size();
		if(v.size()>width)
		{
			step=v.size()/width;
			border=width;
		}

		int min=*std::min_element(v.begin(), v.end());
		int max=*std::max_element(v.begin(), v.end());

		

		for (uint i = 0; i<border-1;i=i+1) {
			cairo_move_to (cr, (double) mapValue(0,border,0,width,i)+offset_x, (double) height - mapValue(min,max,0,height,v.at(i*step))+offset_y );
			cairo_line_to (cr, (double) mapValue(0,border,0,width,i+1)+offset_x, (double) height - mapValue(min,max,0,height,v.at(i*step+step))+offset_y );
			cairo_stroke (cr);
		}
	}
	return true;

}


void paintV2d(Eigen::Vector2d vect, cairo_t *cr, double offsetx,double offsety){
	cairo_move_to(cr,offsetx,offsety);
	cairo_line_to(cr,offsetx+vect(0),offsety+vect(1));
	cairo_stroke(cr);
}

void pofOrigin::paint(cairo_t* cr, const rect& frame){

	double x = _offset(0);
	double y = _offset(1);

	double x1=frame.getx1();
	double y1=frame.gety1();

	double x2=frame.getx1()+frame.getwidth();
	double y2=frame.gety1()+frame.getheight();

	if(x1<x && x<x2){ //vertical line
		paintline(cr,x,y1,x,y2);
	}
	if(y1<y && y<y2){ //horizontal line
		paintline(cr,x1,y,x2,y);
	}

}



