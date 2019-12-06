#ifndef ARGUMENTS
#define ARGUMENTS

#include <pthread.h>

struct Thread_Argument
{ 
    pthread_t * pid;
    int thread_id;
    int * shutdown_flag;
    int * pins_1;
    int * pins_2;
    volatile int * ptr;
    volatile float * sonar_ptr;
};

#endif /* ARGUMENTS */
