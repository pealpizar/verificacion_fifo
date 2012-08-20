
#include "fifo_data_monitor.hpp"

#define TRANSACTIONS ( DATA_LENGTH/8 )

void fifo_mon::prc_fifo_mon()
{

   for(int i = 0 ; i < TCOUNT ; i++ )
   {
      coverage.coverage = fmodel.read(data);
      switch( coverage.coverage )
      {
         case FIFO_FULL:
            coverage.STATUS = PASS;
            break;
         case FIFO_EMPTY:
            coverage.STATUS = PASS;
            break;
         case DATA_CORRUPTION:
            coverage.status = FAIL;
            break;
         case DATA_EQUAL:
            coverage.status = PASS;
            break;
         default:
            coverage.coverage = UNKNOWN;
            coverage.status = ERROR;
            break;
            
      }
      scoreboard.log(coverage);
   }

   

}





