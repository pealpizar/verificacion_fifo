#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <queue>
#include <iostream>
#include <stdio.h>

#include "verification_defs.hpp"
typedef struct coverage_stats_s
{
   unsigned pass;
   unsigned fail;
}coverage_stats_t;

class scoreboard_c
{
   public:
      scoreboard_c();
      ~scoreboard_c();

      log(log_t log_entry );
      write_report();

   private:
      stats();
      deque<log_t> log;
      vector<coverage_stats_t> coverage_stats;
      // log file to save the reports
      FILE logFile;
      // space for up to 100 descriptions
      // and up to 100 characters each
      char coverageDes [100][100];
      char statusDes   [100][100];      [

      write_log();
      write_stats();
      calc_stats();
};

#endif /* __SCOREBOARD_H__ */
