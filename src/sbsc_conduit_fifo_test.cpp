/*
 * sbsc_conduit_fifo_test.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 */

#include "systemc.h"
#include "sbsc_conduit_fifo_test.h"

using namespace sc_core;
using namespace sbsc;

SC_HAS_PROCESS(sbsc_conduit_fifo_test);


sbsc_conduit_fifo_test::sbsc_conduit_fifo_test(
		sc_module_name name
)
:
  sc_module(name)
, my_conduit_fifo(sc_gen_unique_name("scf_"))
{
	qty_errs = 0;
	ix = 0; jx = 0;
	// to bind a signal to the output port
	my_conduit_fifo.iport(port_that_sends_to_conduit);
	port_that_gets_from_conduit(my_conduit_fifo.oport);
	empty(my_conduit_fifo.empty);
	full(my_conduit_fifo.full);

	// sig_out(port_that_sends_to_conduit);
	// sig_in(port_that_gets_from_conduit);

	SC_THREAD(producer);
	sensitive << port_that_gets_from_conduit.read();
	SC_THREAD(consumer);
	sensitive << port_that_sends_to_conduit.write();
}


sbsc_conduit_fifo_test::producer(void)
{	// create 'random' data
	// place it in the fifo conduit
	while ((!full) && (ix < MAX_PRODUCED))
	{
		port_that_sends_to_conduit.write(sc_lv<16>(1000+ix));
		ix++;
		cout << "wrote to fifo: " << (1000 + ix) << tout << endl;
	}
	next_trigger(2, SC_NS);
}


void sbsc_conduit_fifo_test::consumer (void)
{
	if ((!empty) || (!not_enough_data))
	{
		tout = port_that_gets_from_conduit.read();
		vals_out[jx] = tout;
		cout << "tout = " << tout << endl;
	}

	next_trigger(5, SC_NS);
}
