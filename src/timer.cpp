/*
 * timer.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#include "timer.h"

//TODO: FIX UP THE SIGNAL AND PORT HANDLING FOR START
void timer::run_timer() {

	while (true) {
		if (start->read()) {
			cout	<< "Timer: Timer Start Detected @"
					<< sc_time_stamp()
					<< endl;

			count = 5;
			timeout.write(false);
			sig_start.write(false);

		} else {

			if (count > 0) {
				count--;
				timeout->write(true);

			} else {
				timeout->write(true);
			}
		}
		wait();
	}

}

