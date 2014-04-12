/*
 * sbsc_sbuf.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 *
 * Base class for all sbuf types
 * Abstract version - only used as base for real devices
 */

#ifndef SBSC_SBUF_H_
#define SBSC_SBUF_H_

#include "systemc.h"

namespace sbsc {

template<int WIDTH=16>
class sbsc_sbuf: public sc_core::sc_module {
public:

	virtual sbsc_sbuf(sc_core::sc_time d) {
		set_delay(d);
	};

	virtual ~sbsc_sbuf() {
		set_delay(sc_core::SC_ZERO_TIME);
	};

	void set_delay(sc_core::sc_time tm) {
		delay = tm;
	};

	sc_core::sc_time get_delay(void) {
		return delay;
	}

private:

	sc_core::sc_time delay;

};

} /* namespace sbsc */
#endif /* SBSC_SBUF_H_ */
