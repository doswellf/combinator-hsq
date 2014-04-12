/*
 * run_csmplx_tb.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 */

#include "systemc.h"
#include "sbsc_conduit_simplex.h"
#include "sbsc_conduit_simplex_test.h"
#include <iostream>
#include <iomanip>


#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
	const static int DEPTH = 32;
#endif

using namespace std;
using namespace sc_core;
using namespace sbsc;

int sc_main(int argc, char** argv)
{
	int ix;


	sbsc_conduit_simplex_test sbcx("sbcx");

	sc_signal<sc_logic> clken;
	sc_signal<bool> sig_clock;

	sc_clock dc("clk1", 10, SC_NS);
	sbcx.port_clock(sig_clock);

	sc_time interval(10, SC_NS);

	cout << ">>>>> M1 <<<<< " << endl;

	sig_clock.write(dc);


	cout << ">>>>> M2 <<<<< " << endl;

	cout << "WIDTH: " << WIDTH << endl;
	cout << "DEPTH: " << DEPTH << endl;
	cout << "DELAY: " << DELAY << endl;
	cout << "\n ======================================== \n " << endl;

	clken.write(sc_logic('0'));
	sc_start(interval);
	clken.write(sc_logic('1'));
	sc_start(4000, SC_NS);

	cout << ">>>>> M3 <<<<< \n" << endl;
	cout << "\n ==========================================================\n"
		 << "    FINAL VALUES IN EXPECTED AND OUTPUT ARRAYS\n"
		 << "\n ==========================================================\n"
		 << endl;

	for (ix=0; ix < 100; ix++)
		cout << "sbcx.vals_expect["
		<< setfill('0')
		<< setw(3)
		<< dec
		<< ix << "] = "
		<< setw(4) << hex << sbcx.vals_expect[ix].to_int() << endl;

	cout << "\n ==========================================================" << endl;

	for (ix=0; ix < 100; ix++)
		cout << "sbcx.vals_out[" << setfill('0')
		<< setw(3) << dec
		<< ix << "] = "  << setw(4) << hex
		<< sbcx.vals_out[ix].to_int() << endl;
	cout << "\n ==========================================================" << endl;

	return 0;
};




