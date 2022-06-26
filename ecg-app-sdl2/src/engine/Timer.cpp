
#include "Timer.h"

Timer::Timer() {
	start_time = SDL_GetPerformanceCounter();

}

double Timer::getTime(){
	Uint64 tmp_stop_time=SDL_GetPerformanceCounter();
	double delta =((tmp_stop_time - start_time)*1000) / (double)SDL_GetPerformanceFrequency();
	return delta;
}


void Timer::reset(){
	start_time = SDL_GetPerformanceCounter();
}
