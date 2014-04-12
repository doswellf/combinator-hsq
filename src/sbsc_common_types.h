/*
 * sbsc_common_types.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSC_COMMON_TYPES_H_
#define SBSC_COMMON_TYPES_H_
//
// fractal growth of an hsq processor system and application
// steps:
// 1. build core system with basic resources allocated
//    all fpga resources are configured for use but not allocated
//	  similar to oracle db allocating but not using all of a file system

// 2. core system receives or has instructions
//    instructions tell system how to build application structure
// 3. system uses blocks of configured fpga resources to build application
// 4. system places all configurable devices on a dedicated config/control bus
//	  c&c bus is initially used to configure and build devices
// 	  c&c bus is then used to control and re-configure existing devices
//

// constructor blocks for hsq devices
// these tell the system initializers how to build
// hsq devices and how to connect them together

// config blocks for various hsq (h^2) devices
// these give initial
// consists of config blocks for node controller and node devices

// construct system - for systemc simulation only
// vendor fpga programming and init will be used to do this for real

#include "fpga_resources.h"

namespace sbsc {
typedef enum { sc_in, sc_out, sc_inout } scp_t ;

// sbuf variants - alu in sbuf must be a simple one-op pass-through alu (mirrors map or fold)
typedef enum { SBUF_SIMPLE, SBUF_CONST, SBUF_ALU, SBUF_FIFO, SBUF_LIFO, SBUF_REG } sbuf_t ;

// conduit variants
typedef enum {COND_SIMPLEX, COND_DUPLEX, COND_FIFO, COND_LIFO, COND_ALU, COND_IO, COND_MONAD, COND_ARROW } cond_t;

typedef struct cnsys {
	long int 	size;		// size in 16 CLB blocks
	int 		location;	// RLOC or other absolute fpga address
	int 		biosmem;	// block ram or flash with core seed code
	int 		extsrc[16];	// port to read in more seed code from
		limits;		// max fpga resources for target fpga

} cnsys_t;

// device location on fpga
typedef struct blkloc {
	long rloc;
	long blocknum;
	long devnum;

} blkloc_t;
// device location - used to connect devices

typedef struct dvloc {
	long devnum;
	long portnum;
} dvloc_t;

// location for config and control
// this is used after structure is built.

typedef struct ctrloc {
	long cp_addr;
	long cp_port;
} ctrl_loc_t;

typedef struct cbnode {

} cb_node_t;
//

typedef struct cbapp {

}cb_app_t;

typedef struct cbcomb {

} cb_comb_t;

typedef struct cbsbus {
	int length;
	int width;
	sc_core::sc_time shift_delay;
	sc_core::sc_time itap_delay;
	sc_core::sc_time otap_delay;
	sc_core::sc_time ibuf_delay;
	sc_core::sc_time obuf_delay;
	int *itlocs;	// points to array of ints (itaps into sbus)
	int *otlocs;	// points to array of ints (otaps from sbus)

} cb_sbus_t;

/*
 * sbuf feature flags - set/clear in config block to
 * generate an sbuf with the desired feature set.
 *
 * 	bit 	name		description
 * 	-----------------------------------
 * 	0		empty		provides empty flag
 * 	1		full		provides full flag
 * 	2		warn_empty	provides low threshold warning flag
 * 	3		warn_full	provides high threshold warning flag
 * 	4		clock		synchronized to local node clock
 * 	5		areset		provides async reset
 * 	6		sreset		provides sync  reset
 * 	7		preset		provides preset/preload option
 * 	8		reg			provides a single register
 * 	9		alu			provides a simple map/fold alu
 * 	10		aop_t		alu operation (enum of alu ops)
 * 	11		iobuf		IO Monad sbuf
 * 	12		monad		State Monad sbuf
 * 	13		arrow		Arrow sbuf	(not yet - acts as monad)
 * 	14		reserved
 * 	15		reserved
 */
typedef struct sbpm {
	int depth;		// depth of any fifo stage
	int value;		// initial value for reg
	bool flags[16];

}sbpm_t;

// normal to set width to be -1 or equal to the template WIDTH
// this is for future use and for flexibility in corner cases

// there may be cases where WIDTH is not correct for some device

typedef struct cbsbuf {
	int width;		// BEWARE! this overrides template WIDTH value
	sbuf_t sbtype;	// what kind of sbuf is this?
	sbpm_t sbparms; // kind-specific parameters for sbufs

} cb_sbuf_t;


typedef struct cbitap {

} cb_itap_t;

typedef struct cbotap {

} cb_otap_t;

typedef struct cbalu {

} cb_alu_t;

typedef struct cbsys {

}cb_sys_t;

typedef struct port {
	std::string name;
	unsigned int id;
	long width;
	scp_t sc_port_type;
} port_t;

// simplex conduit
typedef struct cbcs {
	double length;
	sc_core::sc_time fwddel;
	sc_core::sc_time revdel;
	ctrl_loc_t 		 iport;
	ctrl_loc_t 		 oport;
} cb_cond_splx_t;

// initial config for duplex conduit
// no other config needed after construction
// conduit flows are opposite to each other

typedef struct cbcd {
	sc_core::sc_time delay;
	double length;
	port_t fwd_in; // 2 for each simplex
	port_t fwd_out;
	port_t rev_in;
	port_t rev_out;
} cb_cond_dplx_t;

// config for fifo conduit
typedef struct cbcf {
	int width;
	double length;
	sc_core::sc_time delay;
	bool has_empty_flag;
	bool has_full_flag;
	bool has_read_th_flag;
	bool has_write_th_flag;
	int fifo_depth;
} cb_cond_fifo_t;

typedef enum { ITAP_BASE, ITAP_FIFO, ITAP_LIFO, ITAP_MULT_IN, ITAP_MULTI_OUT} itap_t ;


}
#endif /* SBSC_COMMON_TYPES_H_ */
