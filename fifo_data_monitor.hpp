#ifndef __FIFO_DATA_MONITOR__
#define __FIFO_DATA_MONITOR__

#include <queue>
#include "verification_defs.hpp"
#include "srl_fifo_16.h"
#include "scoreboard.hpp"
#include <systemc.h>


// VHD model can hold 32 entries of size DATA_LENGTH
#define FIFO_SIZE DATA_LENGTH
typedef enum state_e
{
   NOP,
   READ,
   WRITE,
   RESET,

} state_t;

using namespace std;

typedef sc_lv<8>  data_t;

class fifo_fmodel
{
   public:
      coverage_e write( data_t data) 
      { 
         if( fifo.size() <= FIFO_SIZE )
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
      coverage_e reset()
      {
         return RESET_CORRECT;
      }

   private:
      queue<data_t> fifo; 

};



SC_MODULE (fifo_mon){
  sc_in < sc_lv<8> > data_in, data_out;
  //Aquí las señales de estado no deberían ser necesarias
  sc_in < bool > reset, write, read;
  sc_in_clk      clk;
  log_t report;
  // functional model 
  fifo_fmodel fmodel;
  state_t state;
  data_t data;

  void prc_fifo_mon();
  SC_CTOR (fifo_mon) {
    SC_METHOD (prc_fifo_mon);
      sensitive  <<  clk;
      state = NOP;
  }
};

#endif // __FIFO_DATA_MONITOR__

