/*
 * sbscsbus.h
 *
 *  Created on: Dec 21, 2012
 *      Author: fraser
 */

#ifndef SBSCSBUS_H_
#define SBSCSBUS_H_

#include <systemc.h>

namespace sbsc {

/*
 * This class is mainly structural with the logic expressed in behavioural code
 */

template<int WIDTH=16, int LENGTH=256>
class sbsc_sbus: public sc_core::sc_module {
public:
	sbsc_sbus();
	sbsc_sbus(int, int);
	virtual ~sbsc_sbus();

	sc_in<sc_bool> 		clock   	 	;
	sc_in<sc_bool> 		reset			;
	sc_in<sc_bool>		enable			;
	sc_in<16>  			cnfg_port   	;
	sc_in<16>  			ctrl_port   	;
	sc_out<16> 			status_port 	;
	sc_in<16>			submod_status 	;
	sc_out<sc_logic> 	fault   		;

	// use a pointer to avoid more template params
	sc_in<sc_lv<WIDTH> >	*itaps;
	sc_out<sc_lv<WIDTH> >   *otaps;

private:

	sc_lv<16> cfgmem[MAX_CFG_MEM_SIZE] ;
	sc_lv<16> cfgreg ;
	sc_lv<16> cfgptr ;

	sc_lv<16> ctlmem [MAX_CTL_MEM_SIZE] ;
	sc_lv<16> cfgreg ;
	sc_lv<16> ctlptr ;

	// the actual 'sbus'
	sc_lv<WIDTH> 	sbus[LENGTH];

	int loc_itaps[MAX_ITAP_PER_SBUS];
	int loc_otaps[MAX_OTAP_PER_SBUS];
};

} /* namespace sbsc */
#endif /* SBSCSBUS_H_ */
