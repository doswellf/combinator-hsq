/*
 * sbsc_fifo_connect_example.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: fraser
 */

#include "systemc.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class RGB_frame {

private:

	int r,g,b;

public:

	RGB_frame() {
		r = 0;
		g = 0;
		b = 0;
	}

	RGB_frame(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	int get_red() {
		return r;
	}

	int get_green() {
		return g;
	}

	int get_blue() {
		return b;
	}

	void set(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;

	}

	~RGB_frame() {};


};

class YCrCb_frame {

private:

	int y, cr, cb;

public:

	YCrCb_frame() {
		y = 0;
		cr = 0;
		cb = 0;
	}

	YCrCb_frame(int y, int cr, int cb) {
		this->y = y;
		this->cr = cr;
		this->cb = cb;
	}

	int get_y() {
		return y;
	}

	int get_cr() {
		return cr;
	}

	int get_cb() {
		return cb;
	}

	void set(int y, int cr, int cb) {
		this->y = y;
		this->cr = cr;
		this->cb = cb;

	}

	~YCrCb_frame() {};


};

SC_MODULE(Audio_Mixer) {

	int ctrl_regs[32];
	int channels;
	float master;
	float vols[16];
	float rates[16];

};

SC_MODULE(Mixer_Ctrl) {

	float master_gamma;
	float YCrCb_Percent;
	float RGB_Percent;
};

SC_MODULE (Mixer_State) {
	int ctrl_regs[32];
	bool status_bits[32];
	float sliders[32];
};

SC_MODULE(Rgb2YCrCb) {

	sc_port<sc_fifo_in_if<RGB_frame> > 		port_feeding_rgb_fifo;
	sc_port<sc_fifo_out_if<YCrCb_frame> > 	port_from_ycrcb_fifo;
};

SC_MODULE(YCrCb_Mixer) {

	sc_port<sc_fifo_in_if<float> >			mixer_float_input;
	sc_port<sc_fifo_in_if<YCrCb_frame> >	a_yc_frame_port, b_yc_frame_port;
	sc_port<sc_fifo_out_if<YCrCb_frame> >	yc_mixer_output_port;
};

SC_MODULE(Video_Mixer) {

	// ports
	sc_port<sc_fifo_in_if<YCrCb_frame> > 	dvd_stream_in;
	sc_port<sc_fifo_out_if<YCrCb_frame> > 	video_port_out;
	sc_port<sc_fifo_in_if<Mixer_Ctrl> > 	vidmix_control_port;
	sc_port<sc_fifo_out_if<Mixer_State> > 	status;

	// local channels
	sc_fifo<float> 			K;
	sc_fifo<RGB_frame> 		rgb_graphics;
	sc_fifo<YCrCb_frame> 	ycrcb_graphics;

	// local modules
	Rgb2YCrCb		Rgb2YCrCb_instance;
	YCrCb_Mixer		YCrCb_Mixer_instance;

	// constructor
	Video_Mixer(sc_module_name nm) ;
	void Mixer_Thread();
};

// to go a .cpp (implementation file
// interconnect of preceeding modules

// port connection by name - not using positional notation here
SC_HAS_PROCESS(Video_Mixer);
Video_Mixer::Video_Mixer(sc_module_name nm)
	:
	  sc_module(nm)
	, Rgb2YCrCb_instance   ("Rgb2YCrCb_instance")
	, YCrCb_Mixer_instance ("YCrCb_Mixer_instance")
{

	// Connect modules, ports, channels
	Rgb2YCrCb_instance.port_feeding_rgb_fifo(rgb_graphics);
	Rgb2YCrCb_instance.port_from_ycrcb_fifo(ycrcb_graphics);

	YCrCb_Mixer_instance.mixer_float_input(K);
	YCrCb_Mixer_instance.a_yc_frame_port(dvd_stream_in);
	YCrCb_Mixer_instance.b_yc_frame_port(ycrcb_graphics);
	YCrCb_Mixer_instance.yc_mixer_output_port(video_port_out);
}

// Accessing Ports From Within Processes

// NOTE: sc_fifo_in and sc_fifo_in_if ARE THE OUTPUT END
// OF THE FIFO (CURRENT MODULE IS RECEIVING DATA FROM FIFO)

//
// Using fifo specializations and built-in sensitivity to events
// primitive sc_port does not implement default_event or other
// 'custom' events (custom but provided by the OSCI implementation)


SC_MODULE(Input_Port_Specs) {

	bool ENABLE_SC_BLOCKING_READ;
	// this is for sc_port<sc_fifo_in_if<sc_lv<16> > ports

	sc_fifo_in<sc_lv<16> >  name_fifo_iport;
	sc_lv<16> 				var_value_from_fifo;
	sc_signal<sc_lv<16> > 	sig_value_from_fifo;

	bool fifo_was_empty;
	bool not_empty;
	bool fifo_is_getting_empty;
	bool empty;
	bool iport_was_ready;

	sc_out<sc_lv<16> > my_output_port;

	void Input_Specs_Thread(void) {

		// THREAD KEEPS RUNNING THROUGHOUT THE SIMULATION
		while(1) {

			// wait for a given time
			wait(10, SC_NS);

			// wait for some change on some signal
			// wait(sig_value_from_fifo.value_changed_event());

// INSTEAD OF #ifdef WHICH DID NOT WORK FOR ME HERE
if (ENABLE_SC_BLOCKING_READ) {
			// BLOCKING FIFO READ
			if (!(empty || fifo_was_empty)) {
				name_fifo_iport.read(var_value_from_fifo);
				// OR //
				// assignment override for port read
				// var_value_from_fifo = name_fifo_iport->read();	// use arrow here - NOT DOT!

			}
				// OR //
} else {
			// NON-BLOCKING FIFO READ

			not_empty = name_fifo_iport.nb_read(var_value_from_fifo);
			if (not_empty) {
				// ok to use the value obtained from the fifo
				// this could be done automatically with signals
				// or direct port-to-port connections

				// send value from front of queue out of the port
				my_output_port->write(var_value_from_fifo);

			} else {

				empty = true;
				fifo_was_empty = true;
				// not ok to use the value obtained from the fifo
				// it is not valid - likely garbage or out of date
			}
} // END OF FAKE IFDEF

			// CHECKS ON QTY OF ELEMENTS IN QUEUE
			// ADJUST FLAGS ACCORDING TO EMPTY/FULL CONDITIONS

			if (name_fifo_iport.num_available() > 4) {
				empty = false;
				wait(name_fifo_iport.data_written_event());
			}

			if (name_fifo_iport.num_available() < 8) {
				empty = false;
				fifo_was_empty = true;
				fifo_is_getting_empty = true;
				wait(name_fifo_iport.data_written_event());
			}

			if (name_fifo_iport.num_available() > 8) {
				fifo_was_empty = false;
				empty = false;
				fifo_is_getting_empty = false;
				not_empty = true;
			}

			cout << "sig_value_from_fifo = "
				 << sig_value_from_fifo.read()
				 << endl;
		}

	}

	// METHOD RUNS COMPLETELY THROUGH IN ZERO SIMULATION TIME
	// CONSUMES NO DELTA OR SIMULATOR CLOCK CYCLES

	// CURRENTLY INCOMPLETE - SEE THREAD ABOVE
	void Input_Specs_Method(void) {

		// assignment override for port read
		if (name_fifo_iport.num_available() > 4) {

			var_value_from_fifo = name_fifo_iport->read();	// use arrow here - NOT DOT!
				// OR //
			// offical systemc port read OO version
			name_fifo_iport.read(var_value_from_fifo);

		} else {
			// drop out of the method until next delta cycle
			// or next full clock cycle ???
			next_trigger(name_fifo_iport->data_written_event());
		}

		// using non-blocking read
		if (name_fifo_iport.nb_read(var_value_from_fifo)) {
			// ok to use the value obtained from the fifo
		} else {
			// not ok to use the value obtained from the fifo
			// it is not valid - likely garbage or out of date
		}

		// if fifo is getting depleted, wait until producer
		// puts more values in the other end of the fifo

		// if (name_fifo_iport.num_available() < 4) {
		// 	next_trigger(name_fifo_iport->data_written_event());
		// }
	}

	SC_CTOR(Input_Port_Specs)
	:
	  name_fifo_iport("name_fifo_iport", 32)
	{
		// set all flags to their ' inactive' or de-asserted values

		fifo_was_empty = true;
		fifo_is_getting_empty = true;
		empty = true;
		not_empty = false;
		iport_was_ready = false;

		ENABLE_SC_BLOCKING_READ = true;

		SC_THREAD(Input_Specs_Thread);
		sensitive << name_fifo_iport.data_written_event();
			// OR //
		SC_METHOD(Input_Specs_Method);
		sensitive << name_fifo_iport.data_written_event();
	}

};


// NOTE: THIS IS THE RECEIVING END OF THE FIFO
// 	 	 THE BACK OF THE QUEUE
// 		 FLOW OF DATA IS FROM CURRENT MODULE INTO FIFO
// sc_fifo_out or sc_port<sc_fifo_out_if<T> >

SC_MODULE(Output_Port_Specs) {

	sc_in<sc_lv<16> >		my_input_port;

	sc_fifo_out<sc_lv<16> > name_fifo_oport;
	sc_lv<16> 				var_value_to_fifo;
	sc_signal<sc_lv<16> > 	sig_value_to_fifo;


	bool full;					// fifo currently full
	bool not_full;
	bool fifo_was_full;			// fifo has less than 8 slots free
	bool fifo_is_getting_full;	// fifo has less than 4 slots free
	bool wrote_to_fifo;
	bool port_was_ready;
	bool ok_to_read_from_port;

	void Output_Specs_Thread(void) {

		while (1) {
			// wait for a given time
			wait(10, SC_NS);

			// get a value from the input port
			// var_value_to_fifo = my_input_port.read();
			var_value_to_fifo = my_input_port->read();

			// wait for some change on some signal
			// wait(sig_value_to_fifo.value_changed_event());

			not_full = name_fifo_oport.nb_write(var_value_to_fifo);

			if (not_full) {
				wrote_to_fifo = true;			// value was written to the fifo
				wait(10, SC_NS);				// optional time annotation
				ok_to_read_from_port = true;	// ok to get more data from port

			} else {
				full = true;
				fifo_was_full = true;
				wrote_to_fifo = false;
				fifo_is_getting_full = false;
				ok_to_read_from_port = false;

				// fifo error (fifo full or almost full or other error
				// optionally wait - although that defeats the purpose
				// of a non-blocking write - better to let the kernel work
				// warn user or set a flag value and send it to a port
				// for now we wait - this is a tutorial

				wait (name_fifo_oport->data_read_event());

			}

			// if fifo is getting full, wait until consumer
			// reads more values from the sending end of the fifo

			// this condition would be checked by an event
			// custom event to watch transition on full
			// when full was true then goes false, this
			// flag would be set true

			if (fifo_was_full) {
				// wait a bit longer to start writing to fifo again
				wait (name_fifo_oport->data_read_event());
			}

			if (name_fifo_oport.num_free() < 8 ) {
				fifo_is_getting_full = true;

				wait (name_fifo_oport->data_read_event());
			}

			if (name_fifo_oport.num_free() > 8 ) {
				fifo_is_getting_full = false;
				fifo_was_full = false;
				full = false;
				ok_to_read_from_port = true;
			}

			cout << "sig_value_to_fifo = "
				 << sig_value_to_fifo.read()
				 << endl;
		}
	}

	// notice there is no loop and no wait statements
	// will test wait(N, SC_NS) but do not use event waits
	// only next_trigger may be used
	void Output_Specs_Method(void) {

 		// blocking fifo write
		if (!fifo_is_getting_full && !full && fifo_was_full) {
			name_fifo_oport.write(var_value_to_fifo);
		} else {
			fifo_is_getting_full = true;
			// drop out of the method until
			// more elements are read from fifo
			next_trigger(name_fifo_oport->data_read_event());
		}

		// using non-blocking read
		not_full = name_fifo_oport.nb_write(var_value_to_fifo);
		if (not_full) {
			wrote_to_fifo = true;
			// value was written to fifo - march on!
		} else {

			wrote_to_fifo = false;

			if (name_fifo_oport.num_free() < 8)
				fifo_is_getting_full = true;

			if (name_fifo_oport.num_free() < 4)
				fifo_was_full = true;
			// value was not written - fifo full or almost full
			// other errors are implementation-dependent
		}

	}

	SC_CTOR(Output_Port_Specs)
	:
	  name_fifo_oport("name_fifo_oport")
	, my_input_port("my_input_port")
	{
		not_full = false;
		fifo_was_full = false;
		full = false;
		fifo_is_getting_full = false;
		port_was_ready = false;
		wrote_to_fifo = false;
		ok_to_read_from_port = false;

		sig_value_to_fifo(my_input_port);
		// or
		// my_input_port(sig);
		// ???

		SC_THREAD(Output_Specs_Thread);
		sensitive << name_fifo_oport.data_read_event();

		SC_METHOD(Output_Specs_Method);
		sensitive << name_fifo_oport.data_read_event();
	}
};

