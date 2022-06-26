#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>

#include "signal_processing/filt.h"

std::vector<double> ecg_I; 


int main(){

	std::ifstream is ("data/s0306lre.dat", std::ifstream::binary);
  	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		int length = (is.tellg()*sizeof(char))/sizeof(int);
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


		delete[] buffer;


		//#nofilter
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

 	}

}

