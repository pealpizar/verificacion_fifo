
#include "scoreboard.hpp"

/* **************************************************
 * This is meant to be aligned with coverate_t 
 * definitions
 * **************************************************/
scoreboard_c::scoreboard_c()
{
   logFile.open( "fifo_log.txt" );

   coverageDes[0] = "FIFO_FULL";
   coverageDes[1] = "FIFO_EMPTY";
   coverageDes[2] = "DATA_CORRUPTION";
   coverageDes[3] = "DATA_EQUAL";
   coverageDes[4] = "FIFO_WRITE";
   coverageDes[5] = "RESET_CORRECT";
   coverageDes[6] = "DATA_PRESENT_CORRECT";
   coverageDes[7] = "HALF_FULL_SIGNAL";
   coverageDes[8] = "FULL_SIGNAL";
   coverageDes[99] = "UNKNOWN";


   statusDes[0] = "FAIL";
   statusDes[1] = "PASS";

   coverage_stats.resize(100);
}
scoreboard_c::~scoreboard_c()
{
   logFile.close();
}
void scoreboard_c::log(log_t log_entry )
{
   data_log.push_back(log_entry);
}

void scoreboard_c::write_log()
{
   logFile << "EVENTS LOGGED ----- BEGIN -----" << endl;

   for( int i = 0 ; i < data_log.size() ; i++ )
   {
      // converting to text the log data 
      // sent to the scoreboard
      int idx = (int) data_log[i].status;
      logFile << statusDes[idx] << "\t" ;
      idx = (int) data_log[i].coverage;
      logFile << coverageDes[idx] << endl ;
   }

   logFile << "EVENTS LOGGED -----  END  -----" << endl;
}
void scoreboard_c::calc_stats()
{
   for( int i = 0 ; i < data_log.size() ; i++ )
   {
      int idx  = (int) data_log[i].coverage;
      status_t result = data_log[i].status;

      if(result == PASS) { coverage_stats[idx].pass++; }
      else {coverage_stats[idx].fail++;}
   }
}
void scoreboard_c::write_stats()
{
   unsigned totalPass = 0;
   unsigned totalFail = 0;

   logFile << "SUMMARY ------ BEGIN ------" << endl;
   for( int i = 0 ; i < 100 ; i++ )
   {
      
      logFile << "COVERAGE POINT:\t" << coverageDes[i] ;
      logFile << " PASS:\t" << coverage_stats[i].pass ;
      logFile << " FAIL:\t" << coverage_stats[i].fail ;
      logFile << endl;
      totalPass += coverage_stats[i].pass;
      totalFail += coverage_stats[i].fail;
   }
   logFile << endl;
   logFile << "TOTAL PASS:\t" << totalPass ;
   logFile << " TOTAL FAIL:\t" << totalFail ;
   logFile << endl;
   logFile << "SUMMARY ------  END  ------" << endl;
}

void scoreboard_c::write_report()
{
   calc_stats();
   write_log();
   write_stats();
}


