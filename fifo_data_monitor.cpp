
#include "fifo_data_monitor.hpp"

void fifo_mon::prc_fifo_mon()
{
   switch( state )
   {
      NOP:
         break;
      READ:
         report.coverage = fmodel.read(data);
         break;
      WRITE:
         report.coverage = fmodel.write(data);
         break;
      RESET:
         if( reset )
         { 
            report.coverage = fmodel.reset();
         }
         break;
   }
   if( reset )
   {
      if( state == RESET )
      {
         state = NOP;
         goto END;
      }
      else
      {
         state = RESET;
      }
   }
   if( read && !write )
   {
      state = READ;
      data = data_out;
   }
   else if( write && !read )
   {
      state = WRITE;
      data = data_in;
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
      case RESET_CORRECT;
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





