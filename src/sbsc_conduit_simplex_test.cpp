/*
 * sbsc_conduit_simplex_tests.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 * Simple unit tests for sbsc_conduit_simple
 *
 * TODO: Change To Boost::Test Framework or cppunit
 */

#include "sbsc_conduit_simplex_test.h"
#include <iostream>
#include <iomanip>

using namespace sbsc;
using namespace sc_core;
using namespace sc_dt;
using namespace std;


SC_HAS_PROCESS(sbsc_conduit_simplex_test);


sbsc_conduit_simplex_test::sbsc_conduit_simplex_test(sc_module_name name)
:
  sc_module(name)
, m_csx(sc_gen_unique_name("m_csx_"), WIDTH)
, m_drv(sc_gen_unique_name("m_drv_"))
, port_clken("port_clken")
, port_clock("port_clock")
{
	cout << ">>>>> IN CONSTRUCTOR <<<<< " << endl;
	ix = 0; jx = 0;
	cout << ">>>>> C1 <<<<< " << endl;

	// try with a signal to tie out port to driver port
	// m_clken(sig_clken);
	// m_drv.clken(sig_clken);

	// direct port-to-port connection
	m_drv.clock(port_clock);

	m_drv.clken(sig_clken);
	port_clken(sig_clken);

	cout << ">>>>> C2 <<<<< " << endl;

	// connect iport to driver via signal
	m_drv.driver_port(sig_inp);
	m_csx.iport(sig_inp);

	cout << ">>>>> C2 <<<<< " << endl;
	m_csx.oport(sig_out);

	cout << ">>>>> C3 <<<<< " << endl;

	SC_THREAD(test_producer);
	sensitive << m_drv.driver_port;

	cout << ">>>>> C4 <<<<< " << endl;
	SC_THREAD(test_consumer);
	sensitive << m_csx.oport;

	cout << ">>>>> END CTOR <<<<< " << endl;
}

void sbsc_conduit_simplex_test::test_producer(void)
{

	while(1) {

		cout << ">>>>> ENTERING TEST_PRODUCER <<<<< " << endl;

		sig_clken.write(sc_logic('1'));
		wait (20, SC_NS);
		cout << "PRODUCER: driver_port.read = " << m_drv.driver_port.read() << endl;

		vals_expect[ix] = m_drv.driver_port.read();
		ival = vals_expect[ix].to_int();

		cout << "PRODUCER: vals_expect["
				<< setfill('0')
				<< setw(3)
				<< dec
				<< ix << "] = "
				<< setfill('0')
				<< hex
				<< setw(4) << ival << endl;

		wait(20, SC_NS);
		sig_clken.write(sc_logic('0'));
		if (ix < 100)
			ix++;
		else
			ix = 0;
	}

}

void sbsc_conduit_simplex_test::test_consumer(void)
{
	while (1)
	{
		wait(40, SC_NS);
	cout << ">>>>> ENTERING TEST_CONSUMER <<<<< " << endl;
		// trying to receive value using signals
		//vals_out[jx] = port_in_from_conduit.read();
		vals_out[jx] = sig_out.read();
		if (vals_out[jx] == "ZZZZZZZZZZZZZZZZ")
			jval = 0;
		else
			if (vals_out[jx] == "XXXXXXXXXXXXXXXX")
				jval = 0;
		else
			jval = vals_out[jx].to_int();

		cout << "CONSUMER: vals_out["
				<< setfill('0')
				<< setw(3)
				<< dec
				<< jx << "] = "
				<< setfill('0')
				<< hex
				<< setw(4) << jval << endl;

		if (jx < 100)
			jx++;
		else jx = 0;
	}

}

