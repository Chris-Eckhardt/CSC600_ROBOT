#ifndef ARGUMENTS
#define ARGUMENTS

#include <pthread.h>

// STATE DEFINITIONS
#define FULL_STOP 0
#define DRIVE 1
#define REVERSE 2
#define ROTATE 3
#define F_RIGHT 4
#define F_LEFT 5
#define B_RIGHT 6
#define B_LEFT 7
#define CORRECT_ORIENTATION 8
#define LOST_IN_THE_DARK 99

struct Thread_Argument
{ 
    pthread_t * pid;
    int thread_id;
    int * shutdown_flag;
    int * pins_1;
    int * pins_2;
    volatile int * ptr;
    volatile float * sonar_ptr;
    int * STATE;
};

#endif /* ARGUMENTS */
