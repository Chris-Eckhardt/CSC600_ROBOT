#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"
#include "../gpio/gpio_handler.h"
#include "../util/etc.h"

void * light_emitting_thread ( void * args )
{
    
    struct Thread_Argument * params = (struct Thread_Argument *) args;
    int temp_val = 0;

    if(GPIOExport(params->pins_1[0]) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    delay(200);
 
    if(GPIODirection(params->pins_1[0], IN) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }

    while(1) {
        temp_val = GPIORead(params->pins_1[0]);
        *params->ptr = temp_val;
    }
    

    exit(1);
}

void * sonar_thread ( void * args )
{
    struct Thread_Argument * params = (struct Thread_Argument *) args;

        GPIOExport(params->pins_1[0]);
        GPIOExport(params->pins_1[1]);

        while(1)
    {


        /* EXIT FLAG CHECK */
        if((*params->state) == -1)
        {
            GPIOUnexport(params->pins_1[0]);
            GPIOUnexport(params->pins_1[1]);
            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
        delay(30);
    }
    return 0;
}
