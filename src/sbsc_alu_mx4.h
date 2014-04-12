/*
 * sbsc_alumx4.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSC_ALUMX4_H_
#define SBSC_ALUMX4_H_

#include "systemc.h"

namespace sbsc {

class sbsc_alu_mx4: public sc_core::sc_module {
public:
	sbsc_alu_mx4();
	virtual ~sbsc_alu_mx4();
};

} /* namespace sbsc */
#endif /* SBSC_ALUMX4_H_ */
