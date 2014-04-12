/*
 * sbsc_conduit_fifo.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#include "sbsc_conduit_fifo.h"

#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
#endif

namespace sbsc {

// may not need this thread because the fifo is
// structurally connected to the external ports
//void sbsc_conduit_fifo::conduit_thread(void) {
// };

// standard word width is 16 bits for now

sbsc_conduit_fifo::sbsc_conduit_fifo(
		sc_core::sc_module_name name
	)
	:
	  sc_core::sc_module(name)
	, m_scond(sc_gen_unique_name( "csmplx_"))
	, mff("mff", DEPTH)
	// , mfi("mfi")
	// , mfo("mfo")

	{
		// connect fifo input and output ports to
		// internal fifo instance

		// mfi(mff);
		// mfo(mff);

		// trying to use a fifo and ports with signals

		iport(sig_that_feeds_fifo); // conduit input feeds fifo
		oport(sig_that_fifo_feeds); // fifo output feeds conduit output

		// sig_that_feeds_fifo.write(oport.read());
		mff.write(sig_that_feeds_fifo);
		sig_that_fifo_feeds.write(mff.read());
		// oport.write(sig_that_fifo_feeds);

		err_was_full  = false;
		err_was_empty = false;
		// another way to use the fifo without signals if signal connect fails
		// mff.write(sig_that_feeds_fifo);
		// mff.read(sig_that_fifo_feeds);

		// connect outer conduit ports to fifo ports
		// NOTE: Sense of fifo is reverse to that of ports here
		// 	input port connects to 'outgoing' fifo port
		//  output port connects to 'incoming' fifo port

		//TODO: Test this with a separate module test
		//TODO: Build up unit tests and use BOOST TEST or CPPUNIT

		// may not need the thread due to structural connection
		// of fifo ports to conduit external ports

		// a thread that triggers on fifo read/write
		SC_THREAD(conduit_thread);
		sensitive << iport << oport << mff.default_event();

}

// 		ONCE FIFO RECOVERS FROM EMPTY/FULL, AN ERROR BIT MUST BE CLEARED
//		boolean err_was_empty and err_was_full needed here

void sbsc_conduit_fifo::conduit_thread(void) {

	wait (DELAY*2, SC_NS);
	// check on empty and full and watermark conditions
	// send flags to ports depending on internal fifo conditons
	if (mff.num_free() > 4) {
		mff.write(iport.read());
		oport.write(mff.read());
	}

	if (mff.num_free > DEPTH/2)
		err_was_full = false;

	if (mff.num_available > DEPTH/2)
		err_was_empty = false;

	// if empty only allow writes until 1/2 full
	if (mff.num_free == DEPTH) {
		mff.write(iport.read());
		err_was_empty = true;
		empty.write(true);
	}

	// if full then only allow reads from fifo
	// until number of free slots > 16
	if (mff.num_free() > DEPTH/2) {
		full.write(true);
		err_was_full = true;
		oport.write(mff.read());
	}

	// later - reads are suspended after 8 more cycles when not_enough_data is asserted
	// for now suspend immediately if only 4 elements are left
	if (mff.num_available() < 4) {
		not_enough_data.write(true);
		mff.write(iport.read());
	}

	// signal to calling module - this fifo is about to fill up completely
	// reads are allowed - writes will be ignored after next 8 writes
	if (mff.num_available() > 24 ) {
		has_enough_data.write(true);
		oport.write(mff.read());
	}

};

sbsc_conduit_fifo::~sbsc_conduit_fifo() {
	// free fifo, ports, signals, variables here

}

} /* namespace sbsc */


