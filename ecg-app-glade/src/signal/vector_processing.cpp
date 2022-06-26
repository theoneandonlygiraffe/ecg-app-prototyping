#include "vector_processing.h"


double mapValue(double a0, double a1, double b0, double b1, double a)
{
	return b0 + (b1 - b0) * ((a-a0)/(a1-a0));
}


std::vector<double> deriveVector(const std::vector<double> &v,int h){
	std::vector<double> temp;
	temp.clear();

	if(h>=v.size()/2){
		//h outof bounds
	}
	else if(h==0)
	{
		//ableitung ist aus
		return v;
	}
	else if(h<1)
	{
		//h out of bounds
	}
	else 
	{
		for(int i = 0;i<v.size()-h;i++){
			temp.push_back(v.at(i+h)-v.at(i));
		}
		for(int i = v.size()-h;i<v.size();i++){
			temp.push_back(v.at(i)-v.at(i-h));
		}
	}
	return temp;
}



std::vector<double> filterVector(const std::vector<double> &v,int tabs,int samplingfreq,int filterfreq){
	//#nofilter

	Filter *my_filter;
	std::vector<double> temp;
	temp.clear();

	if(tabs==0) return v;

	my_filter = new Filter(LPF, tabs, samplingfreq, filterfreq);
	if( my_filter->get_error_flag() != 0 ){
		// abort in an appropriate manner
		delete my_filter;
		return v;
	}
	else
	{
		for (uint32_t i = 0; i < v.size(); i++) {
			double next_sample = v.at(i); // Get the next sample from the data stream somehow
			double filtered_sample = my_filter->do_sample( next_sample );
			temp.push_back(filtered_sample);
		}			
	}
	delete my_filter;
	return temp;

}

Eigen::Vector2d v2dfromPolar(double r,double th){
	Eigen::Vector2d vect;
	
	vect(0)=r*cos(th * PI / 180.0);
	vect(1)=r*sin(th * PI / 180.0);

	return vect;
}

Eigen::Vector2d v2dfromPolar(double th){
	Eigen::Vector2d vect;
	
	vect(0)=cos(th * PI / 180.0);
	vect(1)=sin(th * PI / 180.0);

	return vect.normalized();
}

rect getFramefromv2ds(std::vector<Eigen::Vector2d> array){
	if(array.empty()){

	} 
	else
	{	
		double maxX=0, maxY=0, minX=0, minY=0;
		for(int = 0;i<array.size();i++){
			
		}
	}
	
}
