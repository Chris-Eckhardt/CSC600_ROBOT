#ifndef ARGUMENTS
#define ARGUMENTS

#include <pthread.h>

struct Thread_Argument
{ 
    pthread_t * pid;
    int thread_id;
    int * pins_1;
    volatile int * ptr;
    volatile float * sonar_ptr;
};

#endif /* ARGUMENTS */
