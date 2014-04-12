/*
 * sbsc_monad_io.h
 *
 *  Created on: Feb 15, 2013
 *      Author: fraser
 */

#ifndef SBSC_MONAD_IO_H_
#define SBSC_MONAD_IO_H_

#include <systemc.h>

namespace sbsc {

class sbsc_monad_io: public sc_core::sc_module {
public:
	sbsc_monad_io();
	virtual ~sbsc_monad_io();
};

} /* namespace sbsc */
#endif /* SBSC_MONAD_IO_H_ */
