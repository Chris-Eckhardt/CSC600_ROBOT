#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"


struct Thread_Argument * params;

void motor_init();
void forward( int speed );
void motor_run();

void * motor_thread( void * args ) {
    params = (struct Thread_Argument *) args;
    motor_init();
    motor_run();
    return 0;
}

void motor_run()
{
    while(1)
    {
        // 1. check control { state }




        // 2. set motors


    }
}

void forward( int speed )
{
    

}

void motor_init ()
{

}



