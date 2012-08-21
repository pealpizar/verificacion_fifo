
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
      data = data_out;
      report.coverage = fmodel.read(data);
   else if( write && !read )
   {
      data = data_out;
      report.coverage = fmodel.write(data);
   }
   else { goto END; }

   switch( report.coverage )
   {
      case FIFO_FULL:
         report.STATUS = PASS;
         break;
      case FIFO_EMPTY:
         report.STATUS = PASS;
         break;
      case DATA_CORRUPTION:
         report.status = FAIL;
         break;
      case DATA_EQUAL:
         report.status = PASS;
         break;
      default:
         report.coverage = UNKNOWN;
         report.status = ERROR;
         break;
   }
   scoreboard.log(coverage);
   END:
   return;
}





