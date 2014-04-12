/*
 * driver_test.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 *
 *      Test harness module for test case driver
 */

#include "systemc.h"
#include "driver.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace sc_core;
using namespace sbsc;

SC_MODULE(driver_test)
{
	sc_signal<sc_lv<16> > sig_driven;
	sc_lv<16> vals_out[100];

	sc_lv<16> tval;
	int  ival;
	driver m_drv;
	int ix;

	sc_in<bool> clock;
	sc_in<sc_logic> clken;

	void test_thread()
	{
		while(1) {
		tval = sig_driven.read();
	    vals_out[ix] = m_drv.driver_port.read();
	    ival = vals_out[ix].to_int();
    	// printf("vals_out[%d] = %016X\n", ival);

    	cout << "vals_out[" << setfill('0') << dec << setw(3) << ix << "] = " << setfill('0') << hex << setw(4) << ival << endl;

		if (ix < 100)
			ix++;
		else
			ix = 0;
		wait(20, SC_NS);
		}
	}


	SC_CTOR(driver_test)
	:m_drv("m_drv")
	{
		ix = 0;
		ival = 0;
		tval = "ZZZZZZZZZZZZZZZZ" ;
		m_drv.clock(clock);
		m_drv.clken(clken);
		m_drv.driver_port(sig_driven);
		SC_THREAD(test_thread);
		sensitive << m_drv.driver_port;
		dont_initialize();
	}

};


int sc_main(int argc, char* argv[])
{

	driver_test dt("dt");
	sc_signal<sc_logic> ce;

	sc_clock dc("dc", 10, SC_NS);

	dt.clken(ce);
	dt.clock(dc);

	ce.write(sc_logic('0'));
	sc_start(10, SC_NS);

	cout << "@" << sc_time_stamp() << " ASSERTING ENABLE" << endl;
	ce.write(sc_logic('1'));
	cout << "@" << sc_time_stamp() << " ASSERTED ENABLE" << endl;

	sc_start(2000, SC_NS);
	cout << "@" << sc_time_stamp() << " DE-ASSERTING ENABLE" << endl;
	ce.write(sc_logic('0'));
	cout << "@" << sc_time_stamp() << " DE-ASSERTED ENABLE" << endl;
	sc_start(20,SC_NS);

	return  0;


}




