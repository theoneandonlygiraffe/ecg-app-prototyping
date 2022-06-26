#include "engine/myEngine.h"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>

//#include "filter.h"
#include "filt.h"

appManager app(640,480,60,"pong");

std::vector<double> ecg_I; 


int main(){
	app.start();
	return 0;
}


void udef::setup(){
	std::ifstream is ("s0306lre.dat", std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    int * buffer = new int [length];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    is.read ((char*) buffer,length);

    if (is)
      std::cout << "all characters read successfully.";
    else
      std::cout << "error: only " << is.gcount() << " could be read";
    is.close();

    // ...buffer contains the entire file...


	// array to vector
	uint32_t start=0;
	uint32_t end=10000;
	uint32_t step=10;

	for (uint32_t cursor= start; cursor<end; cursor++){
		ecg_I.push_back((double) *(buffer+start+(cursor*step)));
	}


	//#nofilter
	//gaussSmoothen(ecg_I, 50,ecg_I.size()); 

	Filter *my_filter;
  
	my_filter = new Filter(LPF, 51, 100, 10);
 	if( my_filter->get_error_flag() != 0 ); // abort in an appropriate manner

 	for (uint32_t i = 0; i < ecg_I.size(); i++) {
 		double next_sample = ecg_I.at(i); // Get the next sample from the data stream somehow
		double filtered_sample = my_filter->do_sample( next_sample );

		ecg_I.at(i)=filtered_sample;
	}
 	delete my_filter;

	//output
	for (uint32_t i = 0; i < ecg_I.size(); i++) {
        std::cout << ecg_I.at(i) << std::endl;
    }


    /*for(int i=5;i<10000;i=i+10){
      int data = 0;
      for (int sample=-5;sample<=5;sample++){
        data= data + ((int) *(buffer+i+sample));
      }
      data=data/10;


      std::cout<< data <<std::endl;

      
    }*/

    delete[] buffer;
  }

}

void udef::draw(){ //called while apploop active / fps limited

	line(0,0,app.mousex(),app.mousey(),std_red);

	line(app.width(),0,app.mousex(),app.mousey(),std_blue);

	line(app.width(),app.height(),app.mousex(),app.mousey(),std_green);

	line(0,app.height(),app.mousex(),app.mousey(),std_yellow);


	SDL_SetRenderDrawColor(app.renderer(), 0, 0, 0, 255);




//	drawScreen();

	//events
	SDL_Event temp_events;
	while(SDL_PollEvent(& temp_events)) {

		if(temp_events.type == SDL_QUIT){
			app.stop();
		}


	}
}

