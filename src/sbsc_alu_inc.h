/*
 * sbsc_aluinc.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSC_ALUINC_H_
#define SBSC_ALUINC_H_

#include "systemc.h"

namespace sbsc {

class sbsc_alu_inc: public sc_core::sc_module {
public:
	sbsc_alu_inc();
	virtual ~sbsc_alu_inc();
};

} /* namespace sbsc */
#endif /* SBSC_ALUINC_H_ */
