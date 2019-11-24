#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"
#include "../gpio/gpio_handler.h"
#include "../util/etc.h"

void * light_emitting_sensor ( void * args )
{
    struct Thread_Argument * params = (struct Thread_Argument *) args;
    int temp_val = 0;

    if(GPIOExport(params->pin_1) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    delay(200);
 
    if(GPIODirection(params->pin_1, IN) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }

    /* loop and output sensor status */
    while(1) {
        temp_val = GPIORead(params->pin_1);
        *params->ptr = temp_val;
    }
    exit(1);
}

void * sonar_sensor ( void * args )
{

        while(1)
    {

    }
    return 0;
}
