/*
 * sc_fifo_if_tutor.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: fraser
 *
 * sc_fifo tutorial using sc_fifo_ifs.h
 * create custom fifo for a trivial custom class
 *
 * Blatantly copied from sc_fifo in order to understand
 * the use of sc_fifo_in_if<T> and sc_fifo_out_if<T>
 * Public attributes to be added: empty, full, watermark_high, watermark_low
 * Attributes will be accessed via const reference to prevent change
 * Public methods will also be provided for those who prefer that style
 */

#include "systemc.h"
#include "sysc/communication/sc_fifo_ifs.h"
#include "sysc/communication/sc_communication_ids.h"
#include "sysc/communication/sc_prim_channel.h"
#include "sysc/kernel/sc_event.h"
#include "sysc/kernel/sc_simcontext.h"
#include "sysc/utils/sc_report.h"
#include "sysc/utils/sc_string.h"
#include "sysc/tracing/sc_trace.h"
#include <typeinfo>
#include <queue>

// trivial payload class that contains 10 doubles
class trivial {

public:

	trivial()
	:
	myds({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0})
	{
	}
	~trivial() {}

	void set(int ix, double d) {
		myds[ix] = d;
	}

	double get(int ix) {
		return myds[ix];
	}

private:
	double myds [10];

};

// The pure virtual methods of the interfaces must be implemented in this class
template<class T>
class use_fifo_ifbs
	:
	  public sc_module
	, public sc_fifo_in_if
	, public sc_fifo_out_if
{

public:

		  // constructors - note explicit
		  //TODO: FIND OUT WHAT explicit DOES

		  explicit use_fifo_ifbs( int __size__ = 32)
		  :
		  sc_prim_channel( sc_gen_unique_name("fifo") )
		  {
			  init(__size__);
		  }

		  explicit use_fifo_ifbs(char*  __name__, int __size__ = 32)
		  :
		  sc_prim_channel(__name__)
		  {
			  init(__size__);
		  }

		  // destructor
		  virtual ~use_fifo_ifbs()
		  {
			  delete [] my_buffer;
		  }

		  // interface methods
		  virtual void read(T&);
		  virtual T read();

		  // this one can be optionally overridden with a custom definition
		  virtual void register_port(sc_port_base&, const char*);

		  // non-blocking read
		  virtual bool nb_read(T&);

		  // get the number of available elements
		  virtual int num_available() const
		  {
			  return (qty_readable_elements - qty_elements_read_from_my_buffer);
		  }

		  // blocking write
		  virtual void write(const T&);
		  // non-blocking write
		  virtual bool nb_write(const T&);

		  // get the number of free spaces
		  virtual int num_free() const
		  {
			  return (the_size_of_my_buffer - qty_readable_elements - qty_elements_written_to_my_buffer);

		  }

		  // get the data read event (emitted when data is read from the fifo
		  virtual const sc_event& data_read_event() const
		  {
			  return my_data_read_event;
		  }

		  // other fifo utility methods

		  operator T ()
		  {
			  return read();
		  }

		  sc_fifo<T>& operator = (const T& a)
		  {
			  write( a );
			  return *this;
		  }

		  void trace( sc_trace_file* tf) const;

		  virtual void print( ::std::ostream& = ::std::cout) const;
		  virtual void dump(  ::std::ostream& = ::std::cout) const;

		  virtual const char* kind() const
		  {
			  return "sc_fifo" ;
		  }

		  void buf_init( int );

protected:

		  virtual void update();

		  // support methods

		  void init( int );

		  int my_buffer_size;
		  bool buf_write( const T& );
		  bool buf_read( T& );

protected:

		  int the_size_of_my_buffer;
		  int qty_elements_written_to_my_buffer;
		  int qty_elements_read_from_my_buffer;

		  T* my_buffer;
		  int my_free_spaces;
		  int next_read_index;
		  int next_write_index;

		  sc_port_base* my_reader;
		  sc_port_base* my_writer;

		  int qty_readable_elements;

		  sc_event my_data_read_event;
		  sc_event my_data_write_event;



private:

		 // disabled
		 use_fifo_ifbs( const sc_fifo<T>& );
		 use_fifo_ifbs& operator = (const sc_fifo<T>& );


};

// ====================== methods declared external to class body ===================

// register port - assign ports and check for more than one connection on each end

template <class T>
inline
void
use_fifo_ifbs<T>::register_port(
	  sc_port_base& __port__
	, const char* __if_typename__
)
{

	std::string nm( __if_typename__);
	if( nm == typeid( sc_fifo_in_if<T>).name()) {
		// only one reader can be connected
		if (my_reader != 0) {
			SC_REPORT_ERROR( SC_ID_MORE_THAN_ONE_FIFO_READER_, 0);
		}

		my_reader = &__port__;

	} else {
		// only one writer can be connected at one time
		if (my_writer != 0)  {
			SC_REPORT_ERROR(SC_ID_MORE_THAN_ONE_FIFO_WRITER_, 0);
		}
		my_reader = &__port__ ;
	}
}

// blocking read
template <class T>
inline
void
use_fifo_ifbs<T>::read(T& __val__ )
{
	while(num_available() == 0) {
		sc_core::wait( my_data_written_event );
	}
	qty_elements_read_from_my_buffer ++;
	buf_read( __val__ );
	sc_core::request_update();
}


// defined in terms of first form of read method
template<class T>
inline
T
use_fifo_ifbs<T>::read()
{
	T tmp;
	read( tmp );
	return tmp;
}

// non-blocking read
template<class T>
inline
bool
use_fifo_ifbs<T>::nb_read(T& __val__)
{
	if (num_available() == 0) {
		return false;
	}
	qty_elements_read_from_my_buffer ++;
	buf_read(__val__);
	sc_core::request_update();
	return true;
}

// blocking write
template<class T>
inline
void
use_fifo_ifbs<T>::write(const T& __val__)
{
	while( num_free() == 0) {
		sc_core::wait(my_data_read_event );
	}
	qty_elements_written_to_my_buffer ++;
	buf_write(__val__);

}

// non-blocking write
template<class T>
inline
bool
use_fifo_ifbs<T>::nb_write( const T& __val__)
{
	if (num_free() == 0) {
		return false;
	}
	qty_elements_written_to_my_buffer ++;
	buf_write(__val__);
	sc_core::request_update();
	return true;
}

// waveform trace function - only enabled by DEBUG_SYSTEMC define
template<class T>
inline
void
use_fifo_ifbs<T>::trace(sc_trace_file* tf) const
{
#if defined(DEBUG_SYSTEMC)
	char buf[32];
	std::string nm = name();
	for (int i = 0; i < my_size; ++i) {
		std::sprintf(buf, "_%d", i);
		sc_trace(tf, my_buffer[i], nm + buf);
	}
#endif
}

// print fifo contents to stdout
template<class T>
inline
void
use_fifo_ifbs<T>::print( ::std::ostream& os) const
{
	if (my_free_spaces != the_size_of_my_buffer) {
		int i = next_read_index;
		do {
				os << my_buffer[i] << std::endl;
				i = (i + 1) % the_size_of_my_buffer;
		} while (i != next_write_index);
	}
}

template<class T>
inline
void
use_fifo_ifbs<T>::dump( ::std::ostream& os) const
{
	os << "name = " << name() << ::std::endl;
	if (my_free_spaces != the_size_of_my_buffer) {
		int i = next_read_index;
		int j = 0;
		do {
				os << "value[" << i << "] = " << my_buffer[i] << ::std::endl;
				i = (i+1) % the_size_of_my_buffer;
				j ++;
		} while (i != next_write_index);
	}
}

template<class T>
inline
void
use_fifo_ifbs<T>::update()
{
	if (qty_elements_read_from_my_buffer > 0) {
		my_data_read_event.notify(SC_ZERO_TIME);
	}

	if( qty_elements_written_to_my_buffer > 0) {
		my_data_write_event.notify(SC_ZERO_TIME);
	}
		qty_readable_elements = the_size_of_my_buffer - my_free_spaces;
		qty_elements_read_from_my_buffer = 0;
		qty_elements_written_to_my_buffer = 0;
}

// support methods
template<class T>
inline
void
use_fifo_ifbs<T>::init( int __size__)
{
	buf_init(__size__);
	my_reader = 0;
	my_writer = 0;

	qty_readable_elements = 0;
	qty_elements_read_from_my_buffer = 0;
	qty_elements_written_to_my_buffer = 0;
}

template<class T>
inline
void
use_fifo_ifbs<T>::buf_init( int __size__)
{
	if (__size__ <= 0) {
		SC_REPORT_ERROR( SC_ID_INVALID_FIFO_SIZE_, 0);
	}
	the_size_of_my_buffer = __size__;
	my_buffer = new T[the_size_of_my_buffer];
	my_free_spaces = the_size_of_my_buffer;
	next_read_index = 0;
	next_write_index = 0;
}

template<class T>
inline
bool
use_fifo_ifbs<T>::buf_write( const T& __val__ )
{
	if (my_free_spaces == 0 ) {
		return false;
	}
	__val__ = my_buffer[next_read_index];
	next_read_index = (next_read_index + 1) % the_size_of_my_buffer;
	my_free_spaces ++ ;
	return true;
}

// -----------------------------------------------------------------

template<class T>
inline
::std::ostream&
 operator << ( ::std::ostream& os, const use_fifo_ifbs<T>& a)
{
	a.print( os );
	return os;
}
