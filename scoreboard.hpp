#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <queue>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <deque>
#include <fstream>

#include "verification_defs.hpp"
typedef struct coverage_stats_s
{
   unsigned int pass;
   unsigned int fail;
}coverage_stats_t;

class scoreboard_c
{
   public:
      scoreboard_c();
      ~scoreboard_c();

      void log(log_t log_entry );
      void write_report();

   private:
      void stats();
      deque<log_t> data_log;
      vector<coverage_stats_t> coverage_stats;
      // log file to save the reports
      ofstream logFile;
      // space for up to 100 descriptions
      // and up to 100 characters each
      string coverageDes [100];
      string statusDes   [100];     

      void write_log();
      void write_stats();
      void calc_stats();
};

extern scoreboard_c scoreboard;

#endif /* __SCOREBOARD_H__ */
