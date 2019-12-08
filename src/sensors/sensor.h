
#ifndef SENSORS_H
#define SENSORS_H

#include "sensor.c"

void * light_emitting_thread ( void * args );
void * sonar_thread ( void * args );

float getDistance();


#endif /* SENSORS_H */
