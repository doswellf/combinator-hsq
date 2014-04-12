/*
 * sbsc_conduit_fifo_test.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */
// #define BOOST_TEST_MODULE sbsc_fifo_tests
// #include <boost/test/unit_test.hpp>
// #define SC_HAS_DYNAMIC_PROCESSES

#include "systemc.h"
#include "sbsc_conduit_fifo.h"

// create a global object of sbsc_conduit_fifo
// run the methods of sbsc_conduit_fifo using
// pre-defined collections of stimuli
// compare to expected behaviour, output values and flag values

// flags are empty, full, low_water_mark, high_water_mark

// MAX PACKETS PRODUCED FOR THIS SIMULATION

const static long int MAX_PRODUCED  = 10000;

#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
#endif

namespace sbsc {


class sbsc_conduit_fifo_tests : public sc_module
{
public:

	// provide testbench environment

	sbsc::sbsc_conduit_fifo my_conduit_fifo;

	sc_lv<WIDTH>	values_out[500];
	sc_lv<WIDTH>	values_expect[500];
	bool			flags_expect[4];

	int ix,jx;
	int qty_errs;

	sc_in<bool> empty;
	sc_in<bool> full;
	sc_in<bool> has_enough_data;
	sc_in<bool> not_enough_data;

	sc_out<sc_lv<16> > port_that_sends_to_conduit;
	sc_in<sc_lv<16> >  port_that_gets_from_conduit;

	sc_lv<WIDTH> vals_out[500];
	sc_lv<WIDTH> tout;

	sc_signal<sc_lv<WIDTH> > sig_inp;
	sc_signal<sc_lv<WIDTH> > sig_out;

	void producer(void);
	void consumer(void);

	SC_HAS_PROCESS(sbsc_conduit_fifo_tests);
};

}
