/*
 * sbscnode.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSCNODE_H_
#define SBSCNODE_H_

#include "sbsc_sbus.h"
#include "sbsc_sbuf.h"
#include "sbsc_itap.h"
#include "sbsc_otap.h"

#include "systemc.h"
#include <string>

namespace sbsc {

template <
	  int WIDTH=16,    int QTY_INPUT_PORTS=1,  int QTY_OUTPUT_PORTS=1
	, int QTY_SBUS=1,  int SBUS_LENGTH=256,    int QTY_ITAPS=1
	, int QTY_OTAPS=1, int QTY_SBUF=4
>
class sbsc_node: public sc_core::sc_module {
public:
	sbsc_node();
	sbsc_node(WIDTH, std::string);	// width and config string

	// ports - visibility will change as the project matures
	sc_in<sc_lv<16> >    config_port     ;
	sc_in<sc_lv<WIDTH> > iports [QTY_INPUT_PORTS]  ;
	sc_in<sc_lv<WIDTH> > oports [QTY_OUTPUT_PORTS] ;

	virtual ~sbsc_node();

	// this may be protected or private later
	sbsc_node<WIDTH> node_controller ;

private:

	// internal signals and variables
	sc_lv<16>	config_memory 	[100] ;
	sc_lv<16>	status_register		  ;

	// control bus signals from node controller to
	// node sub-modules

	sc_signal<sc_lv<16> > cfg_ctrl_bus [MAX_DEVICE_PER_NODE]	;

	sc_signal<sc_lv<WIDTH> > data_bus  [MAX_ITAP_PER_NODE + MAX_OTAP_PER_NODE] ;

	sc_signal<sc_lv<16> > 	 status_bus ;

};

} /* namespace sbsc */
#endif /* SBSCNODE_H_ */
