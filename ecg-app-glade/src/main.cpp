#include <gtk/gtk.h>

#include <string.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>

#include <bits/stdc++.h>

#include <eigen3/Eigen/Dense>

#include "signal/filt.h"
#include "paint/paint.h"
#include "signal/vector_processing.h"


GtkWidget * entry_input_start;
GtkWidget * entry_input_length;
GtkWidget * entry_input_step;

GtkWidget * entry_processing_h1;
GtkWidget * entry_processing_h2;

GtkWidget * entry_filter_tabs0;
GtkWidget * entry_filter_tabs1;
GtkWidget * entry_filter_tabs2;

GtkWidget * entry_filter_samplingfreq0;
GtkWidget * entry_filter_samplingfreq1;
GtkWidget * entry_filter_samplingfreq2;

GtkWidget * entry_filter_filterfreq0;
GtkWidget * entry_filter_filterfreq1;
GtkWidget * entry_filter_filterfreq2;

GtkWidget * entry_output_scale;


GtkWidget * draw1;
GtkWidget * draw2;



uint ecgcursor_start,ecgcursor_end,ecgcursor=500;



std::vector<double> ecg_I;
std::vector<double> ecg_II;
std::vector<double> ecg_III;
std::vector<double> ecg_aVl;
std::vector<double> ecg_aVr;
std::vector<double> ecg_aVf;

std::vector<double> ecg_v1;
std::vector<double> ecg_v2;
std::vector<double> ecg_v3;
std::vector<double> ecg_v4;
std::vector<double> ecg_v5;
std::vector<double> ecg_v6;


std::vector<double> ecg_I_f1;
std::vector<double> ecg_I_f2;


std::vector<Eigen::Vector2d> ecg_vect;






// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void on_update(GtkButton *b){

	ecg_I.clear();
	ecg_II.clear();
	ecg_III.clear();
	ecg_aVr.clear();
	ecg_aVl.clear();
	ecg_aVf.clear();
	ecg_v1.clear();
	ecg_v2.clear();
	ecg_v3.clear();
	ecg_v4.clear();
	ecg_v5.clear();
	ecg_v6.clear();


	ecg_I_f1.clear();
	ecg_I_f2.clear();

	ecg_vect.clear();

	int start = atoi(gtk_entry_get_text(GTK_ENTRY(entry_input_start)));
	int length = atoi(gtk_entry_get_text(GTK_ENTRY(entry_input_length)));
	int step = atoi(gtk_entry_get_text(GTK_ENTRY(entry_input_step)));

	int h1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_processing_h1)));
	int h2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_processing_h2)));

	int tabs0 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_tabs0)));
	int tabs1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_tabs1)));
	int tabs2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_tabs2)));

	int samplingfreq0 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_samplingfreq0)));
	int samplingfreq1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_samplingfreq1)));
	int samplingfreq2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_samplingfreq2)));

	int filterfreq0 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_filterfreq0)));
	int filterfreq1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_filterfreq1)));
	int filterfreq2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_filter_filterfreq2)));

	



	/*char buffer[128];
  	snprintf(buffer,sizeof(buffer),"start= %d,length= %d,step= %d, \ntabs= %d,samplingfreq= %d,filterfreq= %d",start,length,step,tabs,samplingfreq,filterfreq);
	
 	gtk_label_set_text(GTK_LABEL(label_output),buffer);*/



	//load file

	char* inputfile=NULL;
	gsize input_length;

	//data/patient104/s0306lre.dat
	g_file_get_contents ("../ptb-diagnostic-ecg-database-1.0.0/patient004/s0020are.xyz",&inputfile,&input_length,NULL);

	int ecg_length = input_length/2;//weil short
		
 
	int leads=12;
	// array to vector
	if((start * leads * step) + (length * step * leads) +11>ecg_length){
		//fehler out of bounds
	}
	else if((start * leads * step) + (length * step * leads) +11<1)
	{
		//fehler out of bounds
	}
	else
	{
		for (int cursor= start; cursor<(start+length); cursor++){
		ecg_I.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +0));
		ecg_II.push_back(  (double)   *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +1));
		ecg_III.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +2));
		ecg_aVr.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +3));
		ecg_aVl.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +4));
		ecg_aVf.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +5));

		ecg_v1.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +6));
		ecg_v2.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +7));
		ecg_v3.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +8));
		ecg_v4.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +9));
		ecg_v5.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +10));
		ecg_v6.push_back(  (double)  *( ((short*)inputfile) + (start * leads * step) + (cursor * step * leads) +11));
		}
	}



	ecg_I=filterVector(ecg_I,tabs0,samplingfreq0,filterfreq0);
	ecg_II=filterVector(ecg_II,tabs0,samplingfreq0,filterfreq0);
	ecg_III=filterVector(ecg_III,tabs0,samplingfreq0,filterfreq0);
	ecg_aVr=filterVector(ecg_aVr,tabs0,samplingfreq0,filterfreq0);
	ecg_aVl=filterVector(ecg_aVl,tabs0,samplingfreq0,filterfreq0);
	ecg_aVf=filterVector(ecg_aVf,tabs0,samplingfreq0,filterfreq0);

	for(int i=0; i< ecg_I.size();i++){
		Eigen::Vector2d vect1 = v2dfromPolar(0)*ecg_I.at(i);;
		Eigen::Vector2d vect2 = v2dfromPolar(60)*ecg_II.at(i);
		Eigen::Vector2d vect3 = v2dfromPolar(120)*ecg_III.at(i);
		Eigen::Vector2d vectsum = vect1+vect2+vect3;

		ecg_vect.push_back(vectsum);


	}

	gtk_widget_queue_draw (GTK_WIDGET(draw1));
	gtk_widget_queue_draw (GTK_WIDGET(draw2));

	g_free(inputfile) ;

}

gboolean on_draw1_draw(GtkWidget *widget, cairo_t *cr, gpointer data){

	uint width, height;
	width = gtk_widget_get_allocated_width (widget);   // of draw window

	height = gtk_widget_get_allocated_height (widget); // of draw window

	cairo_set_source_rgb(cr, 1.0, 1.0, 0.0); 
	paint_vector(ecg_I,cr,0,height/6*0,width,height/6);
	cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
	paint_vector(ecg_II,cr,0,height/6*1,width,height/6);
	cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
	paint_vector(ecg_III,cr,0,height/6*2,width,height/6);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	paint_vector(ecg_aVr,cr,0,height/6*3,width,height/6);
	paint_vector(ecg_aVl,cr,0,height/6*4,width,height/6);
	paint_vector(ecg_aVf,cr,0,height/6*5,width,height/6);


	return true;
}

gboolean on_draw2_draw(GtkWidget *widget, cairo_t *cr, gpointer data){

	//float scale = atof(gtk_entry_get_text(GTK_ENTRY(entry_output_scale)));

	float scale=12;


	uint width, height;
	width = gtk_widget_get_allocated_width (widget);   // of draw window
	height = gtk_widget_get_allocated_height (widget); // of draw window

	
	
	rect rect(widget);
	/*rect.x=width/4;
	rect.y=0;
	rect.width=(width/2);
	rect.height=height;*/
	pofOrigin origin(width/2,height/2);

	cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
	origin.paint(cr,rect);

	/*cairo_set_source_rgb(cr, 1.0, 1.0, 0.0);
	paintV2d(vect1,cr,width/2,height/2);
	cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
	paintV2d(vect2,cr,width/2,height/2);
	cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
	paintV2d(vect3,cr,width/2,height/2);

	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	paintV2d(vectsum,cr,width/2,height/2);*/

	origin.setScale(0.1);
	cairo_set_source_rgb(cr, 1, 0.5, 0.5);

	if(ecg_vect.empty()){
		//fehler array leer
	}
	else
	{
		for(int i=10;i<ecg_vect.size()-1;i++){
			//paintline(cr,origin,ecg_vect.at(i),ecg_vect.at(i+1));
			
			Eigen::Vector2d p1;
			Eigen::Vector2d p2;
			p1= (ecg_vect.at(i)*scale)+origin.getoffset();
			p2= (ecg_vect.at(i+1)*scale)+origin.getoffset();

			paintline(cr,p1(0),p1(1),p2(0),p2(1));
			//paintV2d(ecg_vect.at(i)*0.1,cr,width/2,height/2);
		}
	}


	return true;
}


int main(int argc, char *argv[])
{


    GtkBuilder * builder; 
    GtkWidget * window;


	GtkWidget * button_update;


    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");
	
	gtk_builder_add_callback_symbol(builder,"on_window_main_destroy",G_CALLBACK(on_window_main_destroy));
	gtk_builder_add_callback_symbol(builder,"on_update",G_CALLBACK(on_update));
	gtk_builder_add_callback_symbol(builder,"on_draw1_draw",G_CALLBACK(on_draw1_draw));
	gtk_builder_add_callback_symbol(builder,"on_draw2_draw",G_CALLBACK(on_draw2_draw));

	gtk_builder_connect_signals(builder, NULL);

	

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	//g_signal_connect(window,"destroy",G_CALLBACK(on_window_main_destroy),NULL);
	


				entry_input_start= GTK_WIDGET(gtk_builder_get_object(builder,"entry_input_start"));
				entry_input_length= GTK_WIDGET(gtk_builder_get_object(builder,"entry_input_length"));
				entry_input_step= GTK_WIDGET(gtk_builder_get_object(builder,"entry_input_step"));

				entry_processing_h1= GTK_WIDGET(gtk_builder_get_object(builder,"entry_processing_h1"));
				entry_processing_h2= GTK_WIDGET(gtk_builder_get_object(builder,"entry_processing_h2"));

				entry_filter_tabs0= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_tabs0"));
				entry_filter_tabs1= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_tabs1"));
				entry_filter_tabs2= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_tabs2"));

				entry_filter_samplingfreq0= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_samplingfreq0"));
				entry_filter_samplingfreq1= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_samplingfreq1"));
				entry_filter_samplingfreq2= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_samplingfreq2"));

				entry_filter_filterfreq0= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_filterfreq0"));
				entry_filter_filterfreq1= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_filterfreq1"));
				entry_filter_filterfreq2= GTK_WIDGET(gtk_builder_get_object(builder,"entry_filter_filterfreq2"));

				entry_output_scale= GTK_WIDGET(gtk_builder_get_object(builder,"entry_output_scale"));


				button_update= GTK_WIDGET(gtk_builder_get_object(builder,"button_update"));
				
			


			draw1= GTK_WIDGET(gtk_builder_get_object(builder,"draw1"));
			//g_signal_connect(draw_ecg_I,"draw",G_CALLBACK(on_draw_ecg_I_draw),NULL);
			draw2= GTK_WIDGET(gtk_builder_get_object(builder,"draw2"));







	

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}


