/*
 * channel.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#incude "packet.h"
#include "systemc.h"

SC_MODULE(channel) {

	sc_in<packet_t> 		tpackin;
	sc_in<packet_t> 		rpackin;
	sc_out<packet_t> 		tpackout;
	sc_out<packet_t> 		rpackout;

	packet_t packin;
	packet_t packout;
	packet_t ackin;

	void receive_data();
	void send_ack();

	// Constructor
	SC_CTOR(channel) {

		SC_METHOD(receive_data);
		sensitive << tpackin;

		SC_METHOD(send_ack);
		sensitive << rpackin;

	}

};


#endif /* CHANNEL_H_ */
