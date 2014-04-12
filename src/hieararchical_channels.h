/*
 * hieararchical_channels.h
 *
 *  Created on: Jan 10, 2013
 *      Author: Doulos Team
 *
 * How to define Channels in SystemC
 */


// =============== stack_if.h ==========================
#include "systemc.h"

class stack_write_if: virtual public sc_interface
{

public:

	virtual bool nb_write(char) = 0;	// write char to channel
	virtual void reset() = 0;			// empty the stack

};

class stack_read_if: virtual public sc_interface
{

public:

	virtual bool nb_read(char&) = 0;

};

// =============== stack.h ==========================
// implementation of the stack interface methods

#include "systemc.h"
#include "stack_if.h"

class stack
	:
	  public sc_module
	, public stack_write_if
	, public stack_read_if
{

private:

    char data [20]; // the stack
	int top;		// TOS (top of stack)

public:

	// constructor
	stack(sc_module_name nm) : sc_module(nm), top(0)
	{

	}

	bool stack::nb_write(char c)
	{
		if (top < 20)
		{
			data[top++] = c; // post-increment
			return true;
		}
		return false;
	}

	bool stack::nb_read(char& c)
	{
		if (top > 0)
		{
			c = data[--top];	// pre-decrement
			return true;
		}
		return false;
	}

	void stack::register_port(
		  sc_port_base& port_
		, const char* if_typename_
	)
	{
		cout << "binding   " << port.name()
			 << " to ' "
			 << "interface: "
			 << if_typename_ << endl;
	}
};

	  // =============== producer.h ===============
	  // Creating a port and using the stack

#include "systemc.h"
#include "stack_if.h"

class producer : public sc_module
{

public:

	sc_port<stack_write_if> out;
	sc_in<bool> clock;

	void do_writes()
	{

		int i = 0;
		char* TestString = "Hello, This Will Be Reversed" ;
		while (true)
		{
			wait();		// for clock edge
			if (out->nb_write(TestString[i]))
				cout << "W " << TestString[i] << " at "
				<<  sc_time_stamp() << endl;

			i = (i+ 1) % 32 ;
		}
	}

	SC_CTOR(producer)
	{
		SC_THREAD(do_writes);
		sensitive << clock.pos();

	}
};

class consumer : public sc_module
{

public:

	sc_port<stack_read_if> in;
	sc_in<bool> clock;

	void do_reads()
	{

		int i = 0;
		char c;
		char* TestString ;

		TestString = new char[20];

		while (true)
		{
			wait();		// for clock edge
			if (in->nb_read(c)) {
				TestString[i] = c;
				cout << "Received " << c << " at "
					 << sc_time_stamp() << endl;
			}
		}
		cout << "Consumer: Test String: "
			 << TestString << endl;
	}

	SC_CTOR(consumer)
	{
		SC_THREAD(do_reads);
		sensitive << clock.pos();
	}
};

// ============= main.cpp ====================
#include "systemc.h"
#include "stack_if.h"
#include "producer.h"
#include "consumer.h"
#include "stack.h"

int sc_main(int argc, char** argv)
{

	sc_clock ClkFast("ClkFast", 100, SC_NS);
	sc_clock ClkSlow("ClkSlow", 50, SC_NS);

	stack Stack1("S1");

	producer P1("P1");
	P1.out(Stack1);
	P1.clock(ClkFast);

	consumer C1("C1");
	C1.in(Stack1);
	C1.clock(ClkSlow);

	sc_start(5000, SC_NS);

	return 0;

}



