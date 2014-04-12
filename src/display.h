/*
 * display.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

// comms channel monitor/display module

#include "systemc.h"
#include "packet.h"

SC_MODULE(display) {
	sc_in<long> 		din;

	void print_data();

	SC_CTOR(display) {

		SC_METHOD(print_data);
		sensitive << din;
	}
}

#endif /* DISPLAY_H_ */
