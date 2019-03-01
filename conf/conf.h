/* Contains Weaver configuration rules */

// BASIC CONFIGURATION

// The program name as a legible and human-friendly string:
//#define W_PROGRAM_NAME "Program Name"

// The ammount of details printed by weaver functions:
// 0: No warning is printed.
// 1: Info about non-fatal errors will be printed
// 2: General warnings will be printed
// Before installing and distributing this game, set the macro to 0
#define W_DEBUG_LEVEL 2

// This macro determines if we are building a native program (W_ELF) or
// a web program to be run in a browser (W_WEB). In the first case,
// running "make" creates an executable with the project name. In the
// second, creates a "web" directory with a web application
#define W_TARGET W_ELF

//#define W_WIDTH 100
//#define W_HEIGHT 100

// This macro determines if we are writting a C program (W_C) or a C++
// program (W_CPP):
#define W_SOURCE W_C

// The maximum ammount of memory for the game
#define W_MAX_MEMORY 4194304
#define W_INTERNAL_MEMORY 32768
// When compiling for the web, we usually need aditional memory. So we
// sum the memory above with the value below:
#define W_WEB_MEMORY 134217728

// If you wont use multiple threads, you can comment this:
#define W_MULTITHREAD

// If W_MULTITHREAD is defined above, this sets the size of the pool
// of threads used to read and parse files. If the value is zero or
// less, we don't use a pool of threads, but create a new thread each
// time we read and parse a file with audio, font or texture
#define W_THREAD_POOL 1

// The maximum number of Weaver classes that can be defined:
#define W_MAX_CLASSES   100

// Maximum number of instances for each Weaver Object:
#define W_MAX_INSTANCES 100

/* Various Limits */
#define W_MAX_SUBLOOP 16 // Max number of subloops
#define W_MAX_PERIODIC_FUNCTIONS 16 // Max periodic functions in a loop
#define W_MAX_INTERFACES         16 // Max number of interface elements

#define W_DISABLE_PNG
