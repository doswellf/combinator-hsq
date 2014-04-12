/*
 * sbscsbus.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#include "sbsc_sbus.h"

namespace sbsc {

sbsc_sbus::sbsc_sbus(sc_core::sc_module_name name)
	:
	sc_module(name)
	{
		ilsport(sbus[0]);
		olsport(sbus[0]);

		imsport(sbus[LENGTH-1]);
		imsport(sbus[LENGTH-1]);



}

sbsc_sbus::~sbsc_sbus() {
	// TODO Auto-generated destructor stub
}

} /* namespace sbsc */
