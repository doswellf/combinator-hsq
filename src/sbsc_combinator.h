/*
 * sbsc_combinator.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSC_COMBINATOR_H_
#define SBSC_COMBINATOR_H_

#include "systemc.h"

namespace sbsc {

class sbsc_combinator: public sc_core::sc_module {
public:
	sbsc_combinator();
	virtual ~sbsc_combinator();
};

} /* namespace sbsc */
#endif /* SBSC_COMBINATOR_H_ */
