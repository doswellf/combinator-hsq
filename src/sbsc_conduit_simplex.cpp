/*
 * sbsc_conduit_simplex.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 */

#include "sbsc_conduit_simplex.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace sbsc {

	SC_HAS_PROCESS(sbsc_conduit_simplex);

	sbsc_conduit_simplex::sbsc_conduit_simplex(
	    sc_core::sc_module_name name
	    , int width
	)
	:
	  sc_module(name)
	{
		pdelay = sc_time(DELAY, SC_NS);
		length = 1.0;

		// SC_THREAD(read_thread);
		// sensitive << oport;
		// SC_THREAD(write_thread);
		// sensitive << iport;
		SC_THREAD(trans_thread);
		sensitive << iport;
	}

	void sbsc_conduit_simplex::trans_thread(void)
	{
		while(1)
		{

		wait(20, SC_NS);
		// cout << ">>>>> S0 <<<<<" << endl;
		tmp = iport.read();
		if (tmp == "ZZZZZZZZZZZZZZZZ")
			ival = 0;
		if (tmp == "XXXXXXXXXXXXXXXX")
			ival = 0;
		// ival = tmp.to_int();
		// cout << ">>>>> S1 <<<<<" << endl;
		// cout << "sbsc_conduit_simplex iport.read = "
		// 		<< setfill('0') << hex << setw(4) << ival << endl;
		// cout << ">>>>> S2 <<<<<" << endl;
		// wait(DELAY, SC_NS);
		oport.write(iport.read());
		// cout << ">>>>> S3 <<<<<" << endl;
		}
	}

	void sbsc_conduit_simplex::read_thread(void)
	{
		tmp = iport.read();
		wait(DELAY, SC_NS);
	}


	void sbsc_conduit_simplex::write_thread(void)
	{
		oport.write(tmp);
		wait(DELAY, SC_NS);
	}


	sbsc_conduit_simplex::~sbsc_conduit_simplex() {
		length = 0.0;
		pdelay = sc_core::SC_ZERO_TIME;
	}

} /* namespace sbsc */
