#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"

#define stopped 0;
#define forward 0 


void * motor_init ( void * args )
{
    printf("motor int test\n");
    
    struct Thread_Argument * params = (struct Thread_Argument *)args;
    
    if(GPIOExport(params->pin_1) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_2) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    delay(200);
 
    if(GPIODirection(params->pin_1, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
     
    if(GPIODirection(params->pin_2, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    
    //////////////////////////////////////////////////////
    
    GPIOWrite(params->pin_1, HIGH);
 
    return 0;
}



