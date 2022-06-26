#include "rect.h"

rect::rect(GtkWidget* const widget){
	x1=0;
	y1=0;
	width = gtk_widget_get_allocated_width (widget);   // of draw window
	height = gtk_widget_get_allocated_height (widget); // of draw window
}

void rect::operator=(const rect& in){
	x1=in.getx1();
	y1=in.gety1();
	width=getwidth();
	height=getheight();
}