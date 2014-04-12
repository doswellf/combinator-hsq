/*
 * sc_param_mods.h
 *
 *  Created on: Jan 10, 2013
 *      Author: Doulos Team
 *
 * Parameterized Module using Constructor Parameters
 *
 */

#ifndef RAM_H
#define RAM_H

#include "systemc.h"
SC_MODULE(ram) {

  sc_in<bool> clock;
  sc_in<bool> RnW;   // ReadNotWrite
  sc_in<int> address;
  sc_inout<int> data;

  void ram_proc();

  SC_HAS_PROCESS(ram);

  ram(sc_module_name name_, int size_=64, bool debug_ = false) :
    sc_module(name_), size(size_), debug(debug_)
  {
    SC_THREAD(ram_proc);
    sensitive << clock.pos();

    buffer = new int[size];
    if (debug) {
      cout << "Running constructor of " << name() << endl;
    }
  }

  private:
    int * buffer;
    const int size;
    const bool debug;
};

void ram::ram_proc()
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
