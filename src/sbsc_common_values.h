/*
 * sbsc_common_values.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSC_COMMON_VALUES_H_
#define SBSC_COMMON_VALUES_H_

//TODO: Add and adjust values during testing

// constants and static variables for device
// and application component sizes

// these depend on target device resources - adjust per device and model
// eventually this will be an array of properties with a set for each
// device tested so far
namespace sbsc {
const static int MAX_APP_CLBS 			= 32000		;
const static int MAX_APP_BRAM 			= 48		;
const static int MAX_APP_PINS			= 150		;
const static int MAX_BLOCK_SIZE 		= 32		; // # of clb per block allocated
const static int MAX_QTY_BLOCKS 		= 10000		;
const static int MAX_QTY_NODES			= 16000		;
const static int MAX_QTY_CMBNTR			= 1000		;
const static int MAX_QTY_MONAD			= 150		;
const static int MAX_QTY_ARROW			= 150		;
const static int MAX_SBUS_PER_NODE 		= 50	;
const static int MAX_SBUF_PER_NODE  	= 200	;
const static int MAX_ITAP_PER_NODE 		= 100	;
const static int MAX_OTAP_PER_NODE		= 100	;

const static int MAX_ITAP_PER_SBUS		= 64	;
const static int MAX_ITAP_PER_SBUS		= 96	;

const static int MAX_DEVICE_PER_NODE 	= 500	;
const static int MAX_COND_PER_APP		=   250	;
const static int MAX_CFG_MEM_SIZE		= 128	;

const static bool USE_ALTERA_QSYS		= false ;
const static bool USE_AVALON_PROTOCOL	= false	;
const static bool USE_AMBA_PROTOCOL		= false	;
const static bool USE_WISHBONE_PROTOCOL	= false	;
const static bool USE_CUSTOM_PROTOCOL 	= true	;

const static int DEFAULT_WORD_WIDTH		= 16	;
const static int DEFAULT_SBUS_LENGTH	= 256	;
const static int DEFAULT_QTY_ITAPS		= 8		;
const static int DEFAULT_QTY_OTAPS		= 8		;

const static int DEFAULT_QTY_SBUS_PER_NODE 		= 1	;
const static int DEFAULT_QTY_SBUF_PER_NODE 		= 4	;
const static int DEFAULT_QTY_ITAP_PER_NODE		= 8 ;
const static int DEFAULT_QTY_OTAP_PER_NODE		= 8 ;
const static int DEFAULT_QTY_COMB_PER_APP 		= 4	;
const static int DEFAULT_QTY_MONAD_PER_APP		= 4 ;
const static int DEFAULT_QTY_ARROW_PER_APP		= 4 ;
const static int DEFAULT_QTY_CONDUIT_PER_APP	= 8 ;

}
#endif /* SBSC_COMMON_VALUES_H_ */
