
#include "fifo_data_monitor.hpp"

void fifo_mon::prc_fifo_mon()
{
   if( reset == 1 )
   {
      readState = 0;
      writeState = 0;
      goto END:
   }
   if( read && !write )
   {
      readState = 1;
      coverage.coverage = fmodel.read(data);
   else if( write && !read )
   {
      coverage.coverage = fmodel.write(data);
   }
   else { goto END; }

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
   END:
   return;
}





