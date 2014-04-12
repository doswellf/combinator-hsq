/*
 * driver.h
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "systemc.h"
#include <cstdlib>		// for srand and rand
using namespace sc_core;
using namespace sc_dt;

#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
	const static int DEPTH = 32;
#endif

namespace sbsc {
class driver : public sc_module {


public:


	driver(sc_module_name);
	~driver();

	void driver_thread(void);

	int rv;
	sc_in<bool> clock;
	sc_in<sc_logic> clken;
	sc_out<sc_lv<WIDTH> > driver_port;
	sc_lv<WIDTH> tval;
	SC_HAS_PROCESS(driver);


};


}

#endif /* DRIVER_H_ */
