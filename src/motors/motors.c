#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "../util/arguments.h"

struct Thread_Argument * params;
int previous_state = 0;
int state_counter = 0;

void motor_init();
void motor_run();
void test();
void handleState( int state );
void updateMotors();
void followLine();
void stopState();
void forward( int speed );
void backward( int speed );
void hardLeft( int speed );
void hardRight( int speed );

void * motor_thread( void * args ) {
    params = (struct Thread_Argument *) args;
    motor_init();
    //test();
    motor_run();
    return 0;
}

void motor_run() {
    
    //printf("MOTOR_1: %d %d %d\n", params->pins_1[2], params->pins_1[1], params->pins_1[0]); // DEBUG
    //printf("MOTOR_2: %d %d %d\n", params->pins_2[2], params->pins_2[1], params->pins_2[0]); // DEBUG

    while(1)
    {
        handleState(*params->STATE);
        //pdateMotors();
        printf("STATE: %d\n", *params->STATE);
    }
}

// handles any adjustments to motor params that need to be made (if any)
void handleState( int state )
{
    if ( state != previous_state ) state_counter = 0;
    
}

// issues actual commands to motor
void updateMotors()
{
    switch(*params->STATE)
    {
        case 0:
            stopState();
        case 1:
            followLine();
    }
}

// ADVANCED MOTOR COMMANDS

void stopState()
{
    printf("STATE: stopped due to obstruction\n"); /////// TEST
    
    state_counter++;
}

void followLine()
{
    printf("STATE: following path\n"); //////// TEST
    
    state_counter++;
}


// BASIC MOTOR COMMANDS

void forward( int speed )
{
    softPwmWrite(params->pins_2[2], speed);
    digitalWrite(params->pins_2[1], HIGH);
    digitalWrite(params->pins_2[0], LOW);
    
    softPwmWrite(params->pins_1[2], speed);
    digitalWrite(params->pins_1[1], HIGH);
    digitalWrite(params->pins_1[0], LOW);
}

void backward( int speed )
{
    softPwmWrite(params->pins_1[2], speed);
    digitalWrite(params->pins_1[1], LOW);
    digitalWrite(params->pins_1[0], HIGH);

    softPwmWrite(params->pins_2[2], speed);
    digitalWrite(params->pins_2[1], LOW);
    digitalWrite(params->pins_2[0], HIGH);
}

void motor_init ()
{
    pinMode(params->pins_1[2], PWM_OUTPUT);
    pinMode(params->pins_1[1], OUTPUT);
    pinMode(params->pins_1[0], OUTPUT);
    
    pinMode(params->pins_2[2], PWM_OUTPUT);
    pinMode(params->pins_2[1], OUTPUT);
    pinMode(params->pins_2[0], OUTPUT);
    
    softPwmCreate(params->pins_1[2], 0, 100);
    softPwmCreate(params->pins_2[2], 0, 100);
}

void test() 
{
    ////TEST////////////////////////////////////////
    printf("TEST: FORWARD\n");
    
    forward (60);
    delay(10000);
    
    for(int speed = 0; speed <= 100; speed++) {
        forward(speed);
        delay(20);
    }
    printf("slowing down...\n");
    for(int speed = 100; speed >= 0; speed--) {
        forward(speed);
        delay(20);
    }
    printf("stopped...\n");
    
    printf("TEST: REVERSE\n");
    for(int speed = 0; speed <= 100; speed++) {
        backward(speed);
        delay(20);
    }
    printf("slowing down...\n");
    for(int speed = 100; speed >= 0; speed--) {
        backward(speed);
        delay(20);
    }
    printf("stopped...\n");
    ////////////////////////////////////////////////
}



