#include <stdio.h>
#include <stdlib.h>
#include "../util/arguments.h"

#define stopped 0;
#define forward 0 


void * motor_init ( void * args )
{
    printf("motor int test\n");
    
    struct Motor_Arguments * params = (struct Motor_Arguments *)args;
    
    /************* Motor 1 export ****************/
    if(GPIOExport(params->pin_M_1A) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_1B) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_1C) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_1D) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_1E) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_1F) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    /*************** Motor 2 export **************/
    if(GPIOExport(params->pin_M_2A) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_2B) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_2C) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_2D) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_2E) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(params->pin_M_2F) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    /*********** give the kernel a second to build driver *******/
    delay(1000);
 
    /************** set motor 1 pin directions *************/
    if(GPIODirection(params->pin_M_1A, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_1B, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_1C, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_1D, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_1E, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_1F, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }

    /************** set motor 2 pin directions *************/
     if(GPIODirection(params->pin_M_2A, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_2B, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_2C, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_2D, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_2E, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(params->pin_M_2F, OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }

    /*********** init complete ***********/
    return 0;
}



