/*
 * sbsc_sigs.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: fraser
 *
 * Use sigs, threads, methods to pass signal values
 * to a simple internal module and pass external values
 * back out to the sc_main method
 */

#include "systemc.h"
using namespace sc_core;
using namespace sc_dt;

// simple behavioural 2-to-1 mux
SC_MODULE(mux) {

	sc_in<sc_lv<16> > a, b;
	sc_out<sc_lv<16> > x;
	sc_in<sc_logic> sel;

	void mux_thread()
	{
		for (;;)
		{
			wait();
			if (sel == '0')
				x.write(a.read());
			else
				x.write(b.read());
		}
	}

	SC_CTOR(mux) : a("a"), b("b"), x("x"), sel("sel")
	{
		SC_THREAD(mux_thread);
		sensitive << sel << a << b;
	}
};


SC_MODULE(test_mux)
{

	sc_in<sc_lv<16> > ext_a, ext_b;
	sc_out<sc_lv<16> > ext_x;
	sc_in<sc_logic> ext_sel;

	mux my_mux;

	sc_signal<sc_lv<16> > sig_a, sig_b, sig_x;
	sc_signal<sc_logic> sig_sel;

	// method to transfer values back and forth
	// outer test module is just a shell

	void test_method()
	{
		sig_a.write(ext_a.read());
		sig_b.write(ext_b.read());
		sig_sel.write(ext_sel.read());

		ext_x.write(sig_x.read());
	}

	void test_thread()
	{
		while(1)
		{
			wait(1, SC_NS);
			sig_a.write(ext_a.read());
			sig_b.write(ext_b.read());
			sig_sel.write(ext_sel.read());

			ext_x.write(sig_x.read());
			cout << "TEST:THREAD: Transferred Values " << endl;
		}
	}

	SC_CTOR(test_mux) : my_mux("my_mux")
	{

		my_mux.a(sig_a);
		my_mux.b(sig_b);
		my_mux.x(sig_x);
		my_mux.sel(sig_sel);

		// SC_METHOD(test_method);
		SC_THREAD(test_thread);
		sensitive << ext_sel << ext_a << ext_b;
	}

};


int sc_main(int argc, char** argv)
{


	sc_signal<sc_lv<16> > a, b, x;
	sc_signal<sc_logic> sel;


	test_mux mx("mx");
	mx.ext_a(a);
	mx.ext_b(b);
	mx.ext_sel(sel);
	mx.ext_x(x);
	// mux mx("mx");
	// mx.a(a);
	// mx.b(b);
	// mx.x(x);
	// mx.sel(sel);

	cout << ">>>>> M1 <<<<< " << endl;
	cout << "===================================================\n" << endl;
	cout << "Running sc_start for 100 NS ... " << endl;
	sc_start(100, SC_NS);
	cout << "===================================================\n" << endl;

	sel.write(sc_logic('0'));
	a.write("0x0000");
	b.write("0xAAAA");
	cout << ">>>>> M2 <<<<< " << endl;
	cout << "===================================================\n" << endl;
	cout << "Running sc_start for 100 NS ... " << endl;
	sc_start(100, SC_NS);
	cout << "===================================================\n" << endl;

	cout << ">>>>> M3 <<<<< " << endl;
	cout << "a = " << a.read() << endl;
	cout << "b = " << b.read() << endl;
	cout << "sel = " << sel.read() << endl;
	cout << "x = " << x.read() << endl;
	cout << ">>>>> M4 <<<<< " << endl;
	// cout << "===================================================\n" << endl;
	// cout << "Running sc_start for 100 NS ... " << endl;
	// sc_start(100, SC_NS);
	// cout << "===================================================\n" << endl;
	cout << ">>>>> M5 <<<<< " << endl;
	sel.write(sc_logic('1'));
	a.write("0x1111");
	b.write("0xFEED");

	cout << ">>>>> M6 <<<<< " << endl;
	cout << "===================================================\n" << endl;
	cout << "Running sc_start for 100 NS ... " << endl;
	sc_start(100, SC_NS);
	cout << "===================================================\n" << endl;

	cout << ">>>>> M7 <<<<< " << endl;
	cout << "a = " << a.read() << endl;
	cout << "b = " << b.read() << endl;
	cout << "sel = " << sel.read() << endl;
	cout << "x = " << x.read() << endl;
	cout << ">>>>> M8 <<<<< " << endl;
//	cout << "===================================================\n" << endl;
//	sc_start(100, SC_NS);
//	cout << "===================================================\n" << endl;
	return 0;
}
