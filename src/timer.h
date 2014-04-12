/*
 * timer.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "systemc.h"

SC_MODULE(timer) {

	sc_in<bool> 		start;
	sc_out<bool>		timeout;
	sc_in<bool> 		clock;

	sc_signal<bool> 	sig_start;
	int count;

	void run_timer();

	SC_CTOR(timer) {

		SC_THREAD(run_timer);
		sensitive << clock.pos();
		sensitive << start;
		count = 0;

	}
};

#endif /* TIMER_H_ */
