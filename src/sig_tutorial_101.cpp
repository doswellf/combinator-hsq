/*
 * sig_tutorial_101.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: fraser
 *
 * Example - SystemC Signals
 */
#include "systemc.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

// an attempt to make example module content work in sc_main
// if it fails, change this part to a module and create
// sc_main below it.

int sc_main(int argc, char** argv) {

	int count;
	string message_temp;
	sc_signal<int> count_sig;
	sc_signal<string> message_sig;

	sc_start(10, SC_NS);

	// Initializing signals during 1st delta cycle
	count_sig.write(0);
	message_sig.write(string("Hello"));
	count = 11;

	message_temp = "whoa!!!" ;

	cout << "count:\t" << count << "\n"
		 << "count_sig:\t" 		<< count_sig 	<< "\n"
		 << "message_temp:\t" 	<< message_temp << "\n"
		 << "message_sig:\t" 	<< message_sig 	<< endl
		 << "Waiting ..." << endl;

	wait(SC_ZERO_TIME);

	sc_start(10, SC_NS);
	// 2nd delta cycle (eval ->  update ->  eval)
	count = 20;
	count_sig.write(count);

	cout << "count:\t" << count << "\n"
		 << "count_sig:\t" 		<< count_sig 	<< "\n"
		 << "message_temp:\t" 	<< message_temp << "\n"
		 << "message_sig:\t" 	<< message_sig 	<< endl
		 << "Waiting ..." << endl;

	wait(SC_ZERO_TIME);

	sc_start(10, SC_NS);
	// 3rd delta cycle
	message_sig.write(message_temp = "Rev engines");

	cout << "count:\t" << count << "\n"
		 << "count_sig:\t" 		<< count_sig 	<< "\n"
		 << "message_temp:\t" 	<< message_temp << "\n"
		 << "message_sig:\t" 	<< message_sig 	<< endl
		 << "Done." << endl;

	sc_start(10, SC_NS);
	return 0;

}


