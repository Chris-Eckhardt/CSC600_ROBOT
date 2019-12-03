#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"
#include "../util/etc.h"


struct Thread_Argument * params;

void motor_init();
void forward( int speed );
void motor_run();

void * motor_thread( void * args ) {
    printf("motor thread test\n");
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


        /* EXIT FLAG CHECK */
        if((*params->state) == -1)
        {
            printf("!!!! motor_shutdown !!!!\n");
            break;
        }
        delay(30);
    }
}

void forward( int speed )
{
    

}

void motor_init ()
{
    printf("motor init\n");
    printf(" %d %d %d \n", (params->pins_1)[0], (params->pins_1)[1], (params->pins_1)[2]);
}



