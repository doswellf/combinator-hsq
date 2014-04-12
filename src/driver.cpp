/*
 * driver.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 */


#include "driver.h"

namespace sbsc {

SC_HAS_PROCESS(driver);

driver::driver(sc_module_name name)
:
  sc_module(name)
, driver_port("driver_port")
, clock("clock")
, clken("clken")

{
	rv = 0;
	tval = "ZZZZZZZZZZZZZZZZ" ;

	srand(time(NULL));
	SC_THREAD(driver_thread);
	sensitive << clock << clken;

}

driver::~driver()
{
	rv = 0;
}

void driver::driver_thread(void)
{

	rv = 0;
	while(1) {

		rv = 0;
		if (clken == sc_logic('1')) {

			rv = rand() % 2345 ;
			driver_port.write(sc_lv<WIDTH>(rv));

		} else {

			driver_port.write(tval);
		}
		wait(DELAY, SC_NS);
	}
}

} // namespace sbsc
