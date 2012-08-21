
#include "fifo_data_monitor.hpp"

void fifo_mon::prc_fifo_mon()
{
   switch( state )
   {
      case NOP:
         break;
      case READ:
         report.coverage = fmodel.read(data);
         break;
      case WRITE:
         report.coverage = fmodel.write(data);
         break;
      case RESET:
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
      data = data_out.read();
   }
   else if( write && !read )
   {
      state = WRITE;
      data = data_in.read();
   }
   else { goto END; }

   if      ( report.coverage == FIFO_FULL )       { report.status = PASS; }
   else if ( report.coverage == FIFO_EMPTY )      { report.status = PASS; }
   else if ( report.coverage == DATA_CORRUPTION ) { report.status = FAIL; }
   else if ( report.coverage == DATA_EQUAL )      { report.status = PASS; }
   else if ( report.coverage == RESET_CORRECT )   { report.status = PASS; }

   scoreboard.log(report);
   END:
   return;
}





