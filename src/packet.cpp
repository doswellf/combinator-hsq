/*
 * packet.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 *
 * Implementation Of Packet Handling
 *
 */

#include "packet.h"

void sc_trace(
		sc_trace_file *tf
		, const packet_t& v
		, const std::string name
)
{
	sc_trace(tf, v.info  , name + ".info" );
	sc_trace(tf, v.seq   , name + ".seq"  );
	sc_trace(tf, v.retry , name + ".retry");
}




