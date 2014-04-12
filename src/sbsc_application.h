/*
 * sbsc_application.h
 *
 *  Created on: Feb 15, 2013
 *      Author: fraser
 */

#ifndef SBSC_APPLICATION_H_
#define SBSC_APPLICATION_H_

#include "systemc.h"
#include "sbsc_monad_io.h"
#include "sbsc_combinator_composition.h"

using namespace sc_core;
using namespace sc_dt;

namespace sbsc {


template<int WIDTH=16>
	class sbsc_application : public sc_core::sc_module {
	public:
		sbsc_application<WIDTH> (sc_module_name name);
		virtual ~sbsc_application<WIDTH>();

		sbsc_monad_io 	m_mio_1;
		sbsc_monad_io 	m_mio_2;

		sbsc_combinator_composition m_cc_1;
		sbsc_combinator_composition m_cc_2;

		SC_HAS_PROCESS(sbsc_application<WIDTH>);
	};

} /* namespace sbsc */
#endif /* SBSC_APPLICATION_H_ */
