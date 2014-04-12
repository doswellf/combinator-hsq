/*
 * sbsc_conduit_simplex_test.h
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 */

#ifndef SBSC_CONDUIT_SIMPLEX_TEST_H_
#define SBSC_CONDUIT_SIMPLEX_TEST_H_

#include "systemc"
#include "sbsc_conduit_simplex.h"
#include "driver.h"


#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
	const static int DEPTH = 32;
#endif

using namespace sbsc;
using namespace sc_core;

const static int MAX_WORD_PER_SIM = 101;

class sbsc_conduit_simplex_test : public sc_module {

public:

	SC_HAS_PROCESS(sbsc_conduit_simplex_test);

	sbsc_conduit_simplex_test(sc_module_name);

	void test_producer(void);
	void test_consumer(void);

	sc_lv<16> vals_out[MAX_WORD_PER_SIM];
	sc_lv<16> vals_expect[MAX_WORD_PER_SIM];

	sc_in<bool>     port_clock;
	sc_in<sc_logic> port_clken;
	sc_signal<sc_lv<WIDTH> > sig_out;
	sc_signal<sc_lv<WIDTH> > sig_inp;


	sbsc_conduit_simplex m_csx;

	sc_lv<16> tout, tinp;
	int ix,jx;
	int ival_out, ival_expect;
	int ival,jval;
	driver m_drv;

	sc_signal<sc_logic> sig_clken;
	sc_signal<bool> 	sig_clock;
};



#endif /* SBSC_CONDUIT_SIMPLEX_TEST_H_ */
