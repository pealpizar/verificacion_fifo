#ifdef __VERIFICATION_DEFS_H__
#define __VERIFICATION_DEFS_H__


// set default architecture to 16 bits
#define F16

#ifdef F32
#define DATA_LENGTH 32
#elif F16
#define DATA_LENGTH 16
#endif

#extern scoreboard_c scoreboard;

// General definition for coverage points
enum 
{
   FIFO_FULL = 0,          // 0
   FIFO_EMPTY,             // 1
   DATA_CORRUPTION,        // 2
   DATA_EQUAL,             // 3
   RESET_CORRECT,          // 4
   DATA_PRESENT_CORRECT,   // 5
   DATA_LENGTH,            // 6
   HALF_FULL_SIGNAL,       // 7
   FULL_SIGNAL,            // 8

   UNKNOWN = 99,           // 99
} coverage_t;
enum
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
