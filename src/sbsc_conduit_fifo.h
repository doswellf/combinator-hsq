/*
 * sbsc_conduit_fifo.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 *
 *      Conduit with internal sc_fifo
 *
 *      These statements are equivalent
 *      	sc_port<sc_fifo_in_if<sc_lv<16> > > long_fifo_input_port_decl;
 *      		and
 *      	sc_fifo_in<sc_lv<16> > short_fifo_input_port_decl;
 *
 *      	sc_port<sc_fifo_out_if<sc_lv<16> > > long_fifo_output_port_decl;
 *      		and
 *      	sc_fifo_out<sc_lv<16> > short_fifo_output_port_decl;
 *
 *      	For Ports:
 *	      		Use dot notation in constructors (elaboration)
 *      		Use arrow notation in processes to highlight use of port accesses
 */

#ifndef SBSC_CONDUIT_FIFO_H_
#define SBSC_CONDUIT_FIFO_H_

#include "systemc.h"

#include "sbsc_conduit_simplex.h"

#ifndef __SBSC_PARMS__
	#define __SBSC_PARMS__
	const static int WIDTH = 16;	// width of words passing thru conduit
	const static int DELAY = 5;		// SC_NS to wait between operations
	const static int LENGTH = 1;
#endif

namespace sbsc {

class sbsc_conduit_fifo: public sc_core::sc_module {
public:

	SC_HAS_PROCESS(sbsc_conduit_fifo);

	sbsc_conduit_fifo(sc_core::sc_module_name);
	virtual ~sbsc_conduit_fifo();

	void conduit_thread(void);
	// generic in and out ports with fifo
	// between them - a conduit that is a fifo

	sc_in<sc_lv<WIDTH> >  iport;
	sc_out<sc_lv<WIDTH> > oport;
	sc_out<bool> empty;
	sc_out<bool> full;
	sc_out<bool> has_enough_data;
	sc_out<bool> not_enough_data;

	bool err_was_full;
	bool err_was_empty;

	sbsc_conduit_simplex				m_scond;
	// sc_core::sc_fifo_in<sc_lv<WIDTH> > 	mfi;
	// sc_core::sc_fifo_out<sc_lv<WIDTH> >  mfo;
	sc_core::sc_fifo<sc_lv<WIDTH> > 	mff;


	// utility signals to connect iport and oport to conduit ends
	sc_core::sc_signal<sc_lv<WIDTH> >  sig_that_feeds_fifo;
	sc_core::sc_signal<sc_lv<WIDTH> >  sig_that_fifo_feeds;

	// sc_port< sc_fifo_in_if<T> >.
};


} /* namespace sbsc */
#endif /* SBSC_CONDUIT_FIFO_H_ */
