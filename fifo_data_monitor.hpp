#ifdef __FIFO_DATA_MONITOR__

#include <systemc.h>

#include "verification_defs.hpp"
#include "srl_fifo.hpp"
#include "scoreboard.hpp"

// VHD model can hold 32 entries of size DATA_LENGTH
#define FIFO_SIZE DATA_LENGTH

using namespace std;

typedef uint8_t data_t;

class fifo_fmodel
{
   public:
      fifo_fmodel(); 
      status_t write( data_t data) 
      { 
         if( fifo.size() <= FIFO_SIZE )
         {
            return fifo.push( data ); 
         }
         return FIFO_FULL;
      }
      status_t read( data_t data)  
      { 
         if( fifo.empty() )
         {
            return FIFO_EMPTY;
         }
         if( fifo.pop() != data )
         {
            return DATA_CORRUPTION;
         }
         return DATA_EQUAL;
      }
      status_t read( data_t data);

   private:
      queue<data> fifo; 

};



SC_MODULE (fifo_mon){
  sc_in < sc_lv<8> > data_in, data_out;
  //Aquí las señales de estado no deberían ser necesarias
  sc_in < bool > reset, write, read;
  sc_in_clk      clk;
  log_t report;
  // functional model 
  fifo_fmodel fmodel;

  void prc_fifo_mon();
  SC_CTOR (fifo_mon) {
    SC_METHOD (prc_fifo_mon);
      sensitive  <<  clk;
  }
};

#endif // __FIFO_DATA_MONITOR__

