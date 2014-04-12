/*
 * receiver.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#include "receiver.h"

void receiver::receive_data() {

	packin = rpackin->read();

	if (packin = packold) return;

	cout	<< "Receiver: Got Packet #: "
			<< packin.seq
			<< endl;

	if (packin.seq == frame_num) {
		dout = packin.info;
		frame_num++;
		retry++;
		s.retry = retry;
		s.seq = frame_num - 1;
		rpackout->write(s);
	}
	packold = packin;

}



