/*
 * channel_main.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

// main program entry for simplex channel simulation

#include "packet.h"
#include "timer.h"
#include "transmit.h"
#include "receiver.h"
#include "display.h"

int sc_main(int argc, char** argv) {

	sc_signal<packet_t> sig_pkt1, sig_pkt2, sig_pkt3, sig_pkt4;

	sc_signal<long> sig_dout;
	sc_signal<bool> sig_timeout, sig_start;

	// transmit clock
	sc_clock xmit_clock("xmit_clock", 20, SC_NS);
	sc_clock recv_clock("recv_clock", 15, SC_NS);

	// connect
	transmit t1("transmit");
	t1.tpackin(sig_pkt2);
	t1.timeout(sig_timeout);
	t1.tpackout(sig_pkt1);
	t1.start_timer(sig_start);
	t1.clock(xmit_clock);

	channel c1("channel");
	c1.tpackin(sig_pkt1);
	c1.rpackin(sig_pkt3);
	c1.tpackout(sig_pkt2);
	c1.rpackout(sig_pkt4);

	receiver r1("receiver");
	r1.rpackin(sig_pkt4);
	r1.rpackout(sig_pkt3);
	r1.dout(sig_dout);
	r1.rclk(recv_clock);

	display d1("display");
	d1.din(sig_dout);

	timer tm1("timer");
	tm1.start(sig_start);
	tm1.timeout(sig_timeout);
	tm1.clock(xmit_clock);

	// tracing
	// trace file creation
	sc_trace_file *tf = sc_create_vcd_trace_file("simplex");
	// External Signals
	sc_trace(tf, xmit_clock, "xmit_clock");
	sc_trace(tf, sig_timeout, "timeout");
	sc_trace(tf, sig_start, "start");
	sc_trace(tf, sig_pkt1, "signal1");
	sc_trace(tf, sig_pkt2, "signal2");
	sc_trace(tf, sig_pkt3, "signal3");
	sc_trace(tf, sig_pkt4, "signal4");
	sc_trace(tf, sig_dout, "dout");

	sc_start(10000, SC_NS);

	sc_close_vcd_trace_file(tf);

	return 0;

}
