/*
 * packet.h
 *
 *  Created on: Feb 5, 2013
 *      Author: fraser
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "systemc.h"
#include <string>

// modified example code using a typedef
typedef struct pkt {
	long info;
	int seq;
	int retry;

	inline bool operator == (const packet_t& rhs) const
	{
		return (rhs.info == info  && rhs.seq == seq && rhs.retry == retry);
	}

} packet_t;

packet_t pkt_type;

// original example code
struct packet_type {

	long info;
	int seq;
	int retry;
	inline bool operator == (const packet_t& rhs) const
	{
		return (rhs.info == info  && rhs.seq == seq && rhs.retry == retry);
	}

} ;

// define a custom sc_trace method for the packet type
extern
void sc_trace(
		  sc_trace_file *tf
		, const packet_t& v
		, const std::string name
);


#endif /* PACKET_H_ */
