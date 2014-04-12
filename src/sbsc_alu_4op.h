/*
 * sbsc_alu4op.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 *
 * 4 ops are +, -, *, div (integer division)
 * 4 ops are calculated all the time
 * each result is put in an element of result[4]
 * TODO: Test multi-element array ports with simple examples
 * may require inclusion of <cmath> header
 */

#ifndef SBSC_ALU4OP_H_
#define SBSC_ALU4OP_H_

#include "systemc.h"
template<int WIDTH=16>
namespace sbsc {

class sbsc_alu_4op: public sc_core::sc_module {
public:
	sbsc_alu_4op();
	virtual ~sbsc_alu_4op();

	sc_in<sc_lv<WIDTH> >	opnd_a;
	sc_in<sc_lv<WIDTH> >	opnd_b;
	sc_out<sc_lv<WIDTH> >	result[4];

private:

	// scratchpad memory
	int scratch[4];

};

} /* namespace sbsc */
#endif /* SBSC_ALU4OP_H_ */
