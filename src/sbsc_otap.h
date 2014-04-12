/*
 * sbscotap.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSCOTAP_H_
#define SBSCOTAP_H_

#include <systemc.h>

namespace sbsc {

class sbsc_otap: public sc_core::sc_module {
public:
	sbsc_otap();
	virtual ~sbsc_otap();
};

} /* namespace sbsc */
#endif /* SBSCOTAP_H_ */
