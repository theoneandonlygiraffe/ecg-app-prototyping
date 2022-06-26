/*
 * Timer.h
 *
 *  Created on: Mar 23, 2020
 *      Author: alex
 */

#ifndef TIMER_H_
#define TIMER_H_

#include<SDL2/SDL.h>

class Timer {
	public:
		Timer();
		double getTime();
		void reset();
	private:
		Uint64 start_time;

};

#endif /* TIMER_H_ */
