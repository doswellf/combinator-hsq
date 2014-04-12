/*
 * transmit.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef TRANSMIT_H_
#define TRANSMIT_H_

#include "systemc.h"
#include "packet.h"

SC_MODULE(transmit) {

	sc_in<packet_t> 	tpackin;		// input port
	sc_in<bool> 		timeout;		// input port
	sc_out<packet_t>	tpackout		// output port
	sc_inout<bool>		start_timer;	// bidir port
	sc_in<bool>			clock;

	int  buffer;
	int frame_num;
	packet_t packin, tpackold;
	packet_t s;
	int retry;
	bool start;

	void send_data();
	int get_data_from_Application();

	// Constructor
	SC_CTOR(transmit) {

		SC_METHOD(send_data);
		sensitive << timeout;
		sensitive_pos << clock;
		frame_num = 1;
		retry = 0;
		start = false;
		buffer = get_data_from_Application();

	}
};

#endif /* TRANSMIT_H_ */
