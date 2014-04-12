/*
 * receiver.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "systemc.h"
#include "packet.h"

SC_MODULE(receiver) {

	sc_in<packet_t> 		rpackin;
	sc_out<packet_t> 		rpackout;
	sc_out<long> 			dout;
	sc_in<bool> 			rclk;

	int frame_num;
	packet_t packin, packold;
	packet_t s;
	int retry;

	void receive_data();

	SC_CTOR(receiver) {

		SC_METHOD(receive_data) ;
		sensitive << rclk;
		frame_num = 1;
		retry = 1;
	}

};

#endif /* RECEIVER_H_ */
