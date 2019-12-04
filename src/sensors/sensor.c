#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "../util/arguments.h"

struct Thread_Argument * les_args;
struct Thread_Argument * sonar_args;
int timeOut;
double temp;

void * light_emitting_thread ( void * args )
{
    int temp;
    
    les_args = (struct Thread_Argument *) args;
    
    pinMode(les_args->pins_1[0], INPUT);

    while(1) {
        temp = digitalRead(les_args->pins_1[0]);
        *les_args->ptr = temp;

        /* EXIT FLAG CHECK */
        if((*les_args->state) == -1)
        {
            
            printf("!!!! les_shutdown !!!!\n");
            break;
        }
    }
    

    return(0);
}

void * sonar_thread ( void * args )
{
    double temp;
    sonar_args = (struct Thread_Argument *) args;
    
    

    while(1)
    {

        
        /* EXIT FLAG CHECK */
        if((*sonar_args->state) == -1)
        {

            printf("!!!! sonar_shutdown !!!!\n");
            break;
        }
    
    }
    return 0;
}

float getDistance() {
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
    double distance;
	digitalWrite(sonar_args->pins_1[0], LOW);
	delay(2);
	digitalWrite(sonar_args->pins_1[0], HIGH);
	delay(10);
	while(!(digitalRead(sonar_args->pins_1[1]) == 1));
	gettimeofday(&tv1, NULL);
	while(!(digitalRead(sonar_args->pins_1[1]) == 0));
	gettimeofday(&tv2, NULL);
	time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
	time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;
	distance = (double)(time2 - time1) / 1000000 * 34000 / 2;
	return distance;
}
