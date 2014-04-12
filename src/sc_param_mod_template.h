/*
 * sc_param_mod_template.h
 *
 *  Created on: Jan 10, 2013
 *      Author: fraser
 */

#ifndef RAMT_H
#define RAMT_H
#include "systemc.h"

template <class T, int size = 100>
SC_MODULE(ram) {

  sc_in<bool> clock;
  sc_in<bool> RnW;   // ReadNotWrite
  sc_in<int> address;
  sc_inout<T> data;

  void ram_proc();

  SC_HAS_PROCESS(ram);

  ram(sc_module_name name_,  bool debug_ = false) :
    sc_module(name_),  debug(debug_)
  {
    SC_THREAD(ram_proc);
    sensitive << clock.pos();

    buffer = new T[size];
    if (debug) {
      cout << "Running constructor of " << name() << endl;
      cout << "Number of locations is " << size << endl;
    }
  }

  private:
    T * buffer;
    const bool debug;
};

template <class T, int size>
void ram<T,size>::ram_proc()
{
  while(true) {
    wait(); // synchronous to rising edge
    if (RnW) {
      data = buffer[address];
    }
    else {
      buffer[address] = data;
    }
  }
}
#endif
