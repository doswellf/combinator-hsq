/*
 * transmit.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 *
 * Module transmit has the following ports:
 * 	sc_in<packet_t> 	tpackin;
 * 	sc_in<bool>			timeout;
 * 	sc_out<packet_t>	tpackout;
 * 	sc_inout<bool>		start_timer;
 * 	sc_in<bool> 		clock
 *
 * 	tpackin:	receive ack packets from the channel
 * 	timeout		receive timeout signal from timer module
 * 				lets xmit module know that ack packet was not recvd before
 * 				the allowed amount of time
 * 	clock		sync the various modules to a common sc_clock
 * 	tpackout	xmit packets to the channel
 * 	start_timer	used by xmit module to start timer after a packet
 * 				has been sent to the channel
 */

#include "systemc.h"
#include "transmit.h"


int transmit::get_data_from_Application() {

	int result;
	srand(time(NULL)); // seed the rand() generator for more randomness
	result = rand();
	cout 	<< "Generate: Sending Data Value = "
			<< result
			<< endl;

	return result;

}

void transmit::send_data() {
	if (timeout) {
		s.info = buffer;
		s.seq = frame_num;
		s.retry = retry;
		retry++;

		tpackout->write(s);
		start_timer->write(true);
		cout	<< "Transmit: Sending Packet #: "
				<< s.seq
				<< endl;
	} else {
		packin = tpackin.read();
		if (!(packin == tpackold)) {
			if (packin.seq == frame_num) {
				buffer = get_data_from_Application();
				frame_num++;
				retry = 0;
		}

		tpackold = tpackin;
		s.info = buffer;
		s.seq = frame_num;
		s.retry = retry;
		retry++;
		tpackout->write(s);
		start_timer->write(true);
		cout	<< "Transmit: Sending Packet #: "
				<< s.seq
				<< endl;

		}
	}
}

