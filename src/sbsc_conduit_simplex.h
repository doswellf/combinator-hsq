/*
 * sbsc_conduit_simplex.h
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 */

#ifndef SBSC_CONDUIT_SIMPLEX_H_
#define SBSC_CONDUIT_SIMPLEX_H_

#include "systemc.h"

#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
	const static int DEPTH = 32;
#endif

using namespace sc_core;
using namespace sc_dt;

namespace sbsc {

class sbsc_conduit_simplex : public sc_core::sc_module {
public:

	sbsc_conduit_simplex(
		  sc_core::sc_module_name
		, int
	);

	virtual ~sbsc_conduit_simplex();

	void trans_thread(void);
	void read_thread(void);
	void write_thread(void);

	sc_in<sc_lv<WIDTH> >  iport;
	sc_out<sc_lv<WIDTH> > oport;

	sc_lv<WIDTH> tinp,tout;


private:
	sc_lv<WIDTH> tmp, sig_inp, sig_out;
	sc_signal<sc_lv<WIDTH> > sig_val;
	int ival;
	double length;				// virtual length for delay calculations
	sc_core::sc_time pdelay;	// delay per unit of length
};

} /* namespace sbsc */
#endif /* SBSC_CONDUIT_SIMPLE_H_ */
