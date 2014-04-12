/*
 * sbsc_sbuf_in.h
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 */

#ifndef SBSC_SBUF_IN_H_
#define SBSC_SBUF_IN_H_

#include "systemc.h"

namespace sbsc {

template<int WIDTH=16>
class sbsc_sbuf_in: public sc_core::sc_module {

public:

	sbsc_sbuf_in(sc_core::sc_module_name);
	virtual ~sbsc_sbuf_in();

	// transfers input to output with delay
	void sbuf_thread(void);

	sc_in<sc_lv<WIDTH> >  bus_port;
	sc_out<sc_lv<WIDTH> > ext_port;
	sc_out<sc_lv<WIDTH> > debug_port;

private:

	// allows transmission delay to be provided

	sc_lv<WIDTH> value;
	sbsc_sbuf    m_sbuf;
};


} /* namespace sbsc */
#endif /* SBSC_SBUF_IN_H_ */
