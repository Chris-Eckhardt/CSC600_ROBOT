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

        /* EXIT FLAG CHECK */
        if((*params->state) == -1)
        {
            GPIOUnexport(params->pins_1[0]);
            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
    }
    

    exit(1);
}

float getSonar();
long pulseIn(int pin, int level, int timeout);

struct Thread_Argument * sonar_args;
int timeOut;
double temp;

void * sonar_thread ( void * args )
{
    sonar_args = (struct Thread_Argument *) args;

    if(GPIOExport(sonar_args->pins_1[0]) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    if(GPIOExport(sonar_args->pins_1[1]) == -1) {
        printf("exporting pin failed!\n");
        exit(1);
    }
    delay(200);
 
    if(GPIODirection(sonar_args->pins_1[0], OUT) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }
    if(GPIODirection(sonar_args->pins_1[1], IN) == -1) {
        printf("Setting direction pin failed!\n");
        exit(1);
    }

    while(1)
    {

        temp = getSonar();
        *sonar_args->sonar_ptr = temp;


        /* EXIT FLAG CHECK */
        if((*sonar_args->state) == -1)
        {
            GPIOUnexport(sonar_args->pins_1[0]);
            GPIOUnexport(sonar_args->pins_1[1]);
            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
        delay(1000);
    }
    return 0;
}

float getSonar() 
{
    long pingTime;
    float distance;
    GPIOWrite(sonar_args->pins_1[0], HIGH);
    delay(10);
    GPIOWrite(sonar_args->pins_1[0], LOW);
    pingTime = pulseIn(sonar_args->pins_1[1], HIGH, timeOut);
    distance = (float)pingTime * 340.0 / 2.0 / 10000.0;
    return distance;
}

long pulseIn(int pin, int level, int timeout)
{
    // fill this in with the sonar code on the pi
    return 1;
}
