/*
 * sbsc_sbuf_in.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 */

#include "sbsc_sbuf_in.h"

namespace sbsc {

sbsc_sbuf_in::sbsc_sbuf_in(sc_core::sc_module_name name)
	:
	  m_sbuf()
	, sc_core::sc_module(name)
{
	// may not need much code here
}

sbsc_sbuf_in::~sbsc_sbuf_in() {
	// TODO Auto-generated destructor stub
}

} /* namespace sbsc */
