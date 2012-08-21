#ifndef __VERIFICATION_DEFS_H__
#define __VERIFICATION_DEFS_H__


// set default architecture to 16 bits

#ifndef DATA_LENGTH 
#define DATA_LENGTH 16
#endif

using namespace std;

// General definition for coverage points
typedef enum coverage_e
{
   FIFO_FULL = 0,          // 0
   FIFO_EMPTY,             // 1
   DATA_CORRUPTION,        // 2
   DATA_EQUAL,             // 3
   FIFO_WRITE,             // 4
   RESET_CORRECT,          // 5
   DATA_PRESENT_CORRECT,   // 6
   HALF_FULL_SIGNAL,       // 7
   FULL_SIGNAL,            // 8

   UNKNOWN = 99,           // 99
} coverage_t;
typedef enum status_e
{
   FAIL = 0,
   PASS,
} status_t;
typedef struct log_s
{
   status_t status;
   coverage_t coverage;
} log_t;


#endif /* __VERIFICATION_DEFS_H__ */
