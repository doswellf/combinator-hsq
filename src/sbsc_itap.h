/*
 * sbscitap.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 *
 *	Input Tap - Connects to an SBus - This simple version is basically a
 *				SystemC signal or HDL net/wire.
 *				Allows values to be destructively inserted into the sbus
 *				More complex versions will provide splice (non-destructive input)
 *
 *				typedef enum { ITAP_BASE, ITAP_FIFO, ITAP_LIFO,
 *							   ITAP_MULT_IN, ITAP_MULTI_OUT} itap_t
 */

#ifndef SBSCITAP_H_
#define SBSCITAP_H_

#include "systemc.h"
template<int WIDTH=16>
namespace sbsc {

class sbsc_itap: public sc_core::sc_module {
public:
	sbsc_itap();
	virtual ~sbsc_itap();

	sc_in<sc_lv<WIDTH> > src_end;	// input or source end
	sc_out<sc_lv<WIDTH> > bus_end;	// connects to sbus

private:

	itap_t m_type;	// the subtype of this device
	sc_core::sc_time delay;
};

} /* namespace sbsc */
#endif /* SBSCITAP_H_ */
