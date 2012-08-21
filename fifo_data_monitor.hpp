#ifndef __FIFO_DATA_MONITOR__
#define __FIFO_DATA_MONITOR__

#include <queue>
#include "verification_defs.hpp"
#include "srl_fifo_16.h"
#include <systemc.h>

// VHD model can hold 32 entries of size DATA_LENGTH
#define FIFO_SIZE ( 32 * DATA_LENGTH / 8 )

using namespace std;

typedef uint8_t data_t;

class fifo_fmodel
{
   public:
      fifo_fmodel(); 
      coverage_e write( data_t data) 
      { 
         if( fifo.size() < FIFO_SIZE )
         {
            fifo.push( data ); 
            return FIFO_WRITE;
         }
         return FIFO_FULL;
      }
      coverage_e read( data_t data)  
      { 
         if( fifo.empty() )
         {
            return FIFO_EMPTY;
         }
         if( fifo.front() != data )
         {
            fifo.pop();
            return DATA_CORRUPTION;
         }
         fifo.pop();
         return DATA_EQUAL;
      }

   private:
      queue<data_t> fifo; 

};



SC_MODULE (fifo_mon){
  sc_in < sc_lv<8> > data_in, data_out;
  //Aquí las señales de estado no deberían ser necesarias
  sc_in < bool > reset, write, read;
  sc_in_clk      clk;
  log_t log_entry;
  // functional model 
  fifo_fmodel fmodel;

  void prc_fifo_mon();
  SC_CTOR (fifo_mon) {
    SC_METHOD (prc_fifo_mon);
      sensitive << reset << write << read << clk;
  }
};

#endif // __FIFO_DATA_MONITOR__

