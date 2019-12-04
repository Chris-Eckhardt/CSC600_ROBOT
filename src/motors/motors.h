#ifndef MOTORS_H
#define MOTORS_H

#include "motors.c"

void * motor_thread( void * args );
void motor_init();
void forward( int speed );

#endif // MOTORS_H
