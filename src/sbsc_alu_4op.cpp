/*
 * sbsc_alu4op.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 *
 *  Behavioural Model Only
 *  Use with bare systemc or wrap for tlm2
 *  Calculates 4 integer operations
 *  Converts to int and back to sc_lv<WIDTH>
 */

#include "sbsc_alu4op.h"

namespace sbsc {

sbsc_alu_4op::sbsc_alu_4op(sc_core::sc_module_name name)
:
sc_module(name)
{
	// connect ports and provide a thread sensitive to
	// changes to either or both of the inputs

}

sbsc_alu_4op::~sbsc_alu_4op() {
	// TODO Auto-generated destructor stub
}

} /* namespace sbsc */

void sbsc_alu_4op::alu_thread(void) {

	// convert sc_lv<WIDTH> to integer and then perform math
	// then convert int back to sc_lv<WIDTH>
	scratch[0] = opnd_a.to_int() + opnd_b.to_int();
	scratch[1] = opnd_a.to_int() - opnd_b.to_int();
	scratch[2] = opnd_a.to_int() * opnd_b.to_int();

	if (!(opnd_b.to_int() == 0) )
		scratch[3] = opnd_a.to_int() / opnd_b.to_int();
	else
		scratch[3] = -1;

	for (int ix=0; ix < 4; ix++)
		result[ix] = sc_lv(scratch[ix]);

}
