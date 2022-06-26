#ifndef RECT_H_
#define RECT_H_

#include <gtk/gtk.h>

class rect{
	private:
		double x1;
		double y1;
		double width;
		double height;
	public:

		rect(){x1=0;y1=0;width=0;height=0;};
		rect(const rect& in){x1=in.getx1();y1=in.gety1();width=in.getwidth();height=in.getwidth();};
		rect(double _x1,double _y1,double _width,double _height){x1=_x1;y1=_y1;width=_width;height=_height;};
		rect(GtkWidget* const widget);

		void operator=(const rect& in);
		void operator=(const GtkWidget *widget);


		double getx1() const {return x1;};
		double gety1() const {return y1;};
		inline double getx2() const {return x1+width;};
		inline double gety2() const {return y1+width;};
		double getwidth() const {return width;};
		double getheight() const {return width;};

};
/*
class edge{
private:
	double x1,y1;
	double x2,y2;
public:
	edge(){x1=0;y1=0;x2=0;y2=0;};
	edge(double _x1,double _y1,double _x2,double _y2){x1=_x1;y1=_y1;x2=_x2;y2=_y2;};

	void paint(cairo_t* cr);
	bool collideswith(const edge& in);
};*/






#endif //RECT_H_