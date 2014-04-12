/*
 * main.cpp
 */

#define SC_HAS_DYNAMIC_PROCESSES
#include "sbsc_conduit_fifo.h"
#include "sbsc_conduit_fifo_test.h"
#include "systemc.h"

/*
 *  Created on: Jan 19, 2013
 *      Author: fraser
 */

using namespace sc_core;
using namespace sbsc;


int sc_main(int argc, char* argv[])
{
	cout << "\t ***** Instantiating Test Harness Module *****\n" << endl;

	sbsc_conduit_fifo_tests<16,32,5> scft("scft");

	cout << "\t ***** Starting SystemC Simulator For 3000 NS) *****\n" << endl;

	sc_start(3000, SC_NS);

	cout << "\t ***** Completed Simulation For 3000 NS) *****\n" << endl;

	return 0;
}


