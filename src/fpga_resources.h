/*
 * fpga_resources.h
 *
 *  Created on: Jan 7, 2013
 *      Author: fraser
 * Vendor-Specific FPGA Parameters
 *
 */

#ifndef FPGA_RESOURCES_H_
#define FPGA_RESOURCES_H_

#include <string>

// max qty of vendor specs in spec array

const static int MAX_VENDORS = 4;
// fpga parameter values for various vendor fpga devices

const static int VENDOR_XILINX  = 0;
const static int VENDOR_ALTERA  = 1;
const static int VENDOR_LATTICE = 2;

typedef struct fp {
	std::string vendor	;
	std::string family	;
	std::string devroot	;
	std::string devexts	;
	std::string speed	;

	long slices		;
	long clbs		;
	long dsps		;
	long qty_bram	;			// number of bram in fpga
	long rows_bram	;
	long cols_bram	;			// layout of bram
	long bram_size	;			// single bram capacity
	long total_bram	;			// total bram size in KB
	long longlineh	;			// longline connections
	long longlinev	;
	long shortlineh	;
	long shortlinev	;			// short line connections
	long clocklineh	;
	long clocklinev	;			// dedicated clock lines
	long ddrport	;			// any built-in ddr ram ports
	long qty_pins	;			// pins available for hsq

} fp_t;

const static fp_t	fpga_specs[MAX_VENDORS] = {

		{
				"Xilinx"		,
				"Spartan3AN"	,
				"XSC3"			,
				"??????"		,
				"6"				,
				256				,
				1200			,
				16				,
				16				,
				4				,
				4				,
				65536			,
				1048576			,
				32				,
				32				,
				64				,
				64				,
				16				,
				16				,
				0				,
				128
		}
		,
		{
				"Altera"		,
				"CycloneIII"	,
				"EP3C"			,
				"??????"		,
				"6"				,
				256				,
				1200			,
				16				,
				16				,
				4				,
				4				,
				65536			,
				1048576			,
				32				,
				32				,
				64				,
				64				,
				16				,
				16				,
				4				,
				128

		}
		,
		{
				"Lattice"		,
				"ECP3"	,
				"EP3C"			,
				"??????"		,
				"6"				,
				256				,
				1200			,
				16				,
				16				,
				4				,
				4				,
				65536			,
				1048576			,
				32				,
				32				,
				64				,
				64				,
				16				,
				16				,
				16				,
				128

		}

};


#endif /* FPGA_RESOURCES_H_ */
