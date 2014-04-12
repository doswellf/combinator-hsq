/*
 * sc_fifo_tutor.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: fraser
 *
 * send and receive data via fifo at different read and write rates
 *
 */

#include "systemc.h"

class scft : public sc_module {

public:

	SC_HAS_PROCESS(scft);

	scft(sc_core::sc_module_name );
	~scft();

	void read_thread(void);		// reads generated traffic and sends to cout
	void write_thread(void);	// creates traffic and writes it to fifo

	sc_core::sc_fifo<int> my_fifo;
	sc_core::sc_fifo_in<int> my_fifo_input_port;
	sc_core::sc_fifo_out<int> my_fifo_output_port;

	int vals[200];
private:

	int ix, jx;
	int tval;

};


scft::scft(sc_core::sc_module_name name)
	:   sc_module(name)
	  , my_fifo("my_fifo", 150)
{

	tval = 0;
	jx = 0;
	ix = 0;

	for (ix=0; ix < 150; ix++)
		vals[ix] = 0;

	my_fifo_input_port(my_fifo);
	my_fifo_output_port(my_fifo);
	SC_THREAD(read_thread);
		sensitive << my_fifo_input_port.data_written_event();
	SC_THREAD(write_thread);
		sensitive << my_fifo_output_port.data_read_event();

}

scft::~scft() {}

void scft::read_thread(void)
{

	bool there_was_a_number;

	for (;;) {
		for (jx=0; jx < 150; jx++) {
			there_was_a_number = my_fifo_input_port.nb_read(tval);
			if (there_was_a_number) {
				vals[jx] = tval;
				cout << "***** READ THREAD: READ A NUMBER" << endl;
			} else {
				cout << ">>>>> READ THREAD: DID NOT READ A NUMBER" << endl;
			}

		}


		wait(3, SC_NS);
	}
}

void scft::write_thread(void) {

	bool wrote_a_number;
	for (;;) {
		for (ix=0; ix < 200; ix++) {
			wrote_a_number = my_fifo_output_port.nb_write(ix+1000);
			if (wrote_a_number)
				cout << "***** WRITE THREAD: WROTE A NUMBER" << endl;
			else
				cout << ">>>>> WRITE THREAD: DID NOT WRITE A NUMBER" << endl;
		}
		wait(2, SC_NS);
	}
}

int sc_main(int argc, char** argv)
{

	int ix;

	cout << "\t ***** Constructing SC_FIFO Tutorial Simulations ***** " << endl;
	scft mscft("mscft") ;
	cout << "\t ***** Starting SC_FIFO Tutorial Simulations ***** " << endl;
	sc_start(100, SC_NS);
	cout << "\t ***** Examining Contents Of Modules ***** " << endl;
	for (ix=0; ix < 100; ix++)
		cout << "vals[" << ix << "]= " << mscft.vals[ix] << endl;

	cout << "\t ***** Finished SC_FIFO Tutorial A***** " << endl;

	return 0;

}

