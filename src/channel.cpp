/*
 * channel.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#include "channel.h"

void channel::receive_data() {

	srand(time(NULL));

	int i;
	packin = tpackin.read();

	cout	<< "Channel: Received Packet With Seq #: "
			<< packin.seq
			<< endl;

	i = rand();
	packout = packin;
	cout	<< "Channel: Random Number = "
			<< i
			<< endl;

	if ((i > 1000) && (i < 5000)) {
		packout.seq = 0;
	}
	rpackout->write(packout);

}

void channel::send_ack() {

	int i;
	packin = rpackin;
	cout	<< "Channel: Received Ack for Packet Seq #: "
			<< packin.seq
			<< endl;

	packout = packin;

	if ((i > 10) && (i < 500)) {
		packout.seq = 0;
	}

	tpackout->write(packout);
}


