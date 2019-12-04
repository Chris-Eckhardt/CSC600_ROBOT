#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"
#include "../util/etc.h"

struct Thread_Argument * les_args;
struct Thread_Argument * sonar_args;
int timeOut;
double temp;

void * light_emitting_thread ( void * args )
{
    
    les_args = (struct Thread_Argument *) args;


    while(1) {
   

        /* EXIT FLAG CHECK */
        if((*les_args->state) == -1)
        {
  
            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
    }
    

    return(0);
}

void * sonar_thread ( void * args )
{
    sonar_args = (struct Thread_Argument *) args;


    while(1)
    {

        /* EXIT FLAG CHECK */
        if((*sonar_args->state) == -1)
        {

            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
        delay(1000);
    }
    return 0;
}
