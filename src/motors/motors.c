#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "../util/arguments.h"


struct Thread_Argument * params;

void motor_init();
void forward( int speed );
void backward( int speed );
void hardLeft( int speed );
void hardRight( int speed );
void motor_run();

void * motor_thread( void * args ) {
    params = (struct Thread_Argument *) args;
    motor_init();
    motor_run();
    return 0;
}

void motor_run() {

    ////TEST////////////////////////////////////////
    printf("TEST: FORWARD\n");
    for(int speed = 0; speed <= 100; speed++) {
        forward(speed);
        delay(30);
    }
    for(int speed = 100; speed > 0; speed--) {
        forward(speed);
        delay(30);
    }
    printf("TEST: BACKWARD\n");
    for(int speed = 0; speed <= 100; speed++) {
        backward(speed);
        delay(30);
    }
    for(int speed = 100; speed >= 0; speed--) {
        backward(speed);
        delay(30);
    }
    printf("TEST: HARD LEFT\n");
    for(int speed = 0; speed <= 100; speed++) {
        hardLeft(speed);
        delay(30);
    }
    for(int speed = 100; speed >= 0; speed--) {
        hardLeft(speed);
        delay(30);
    }
    printf("TEST: HARD RIGHT\n");
    for(int speed = 0; speed <= 100; speed++) {
        hardRight(speed);
        delay(30);
    }
    for(int speed = 100; speed >= 0; speed--) {
        hardRight(speed);
        delay(30);
    }
    ////////////////////////////////////////////////

    while(1)
    {
        // 1. check control { state }
        


        // 2. set motors


    }
}

void forward( int speed )
{
    pwmWrite(params->pins_1[0], speed);
    pwmWrite(params->pins_2[0], speed);
    digitalWrite(params->pins_1[1], HIGH);
    digitalWrite(params->pins_2[1], HIGH);
    digitalWrite(params->pins_1[2], LOW);
    digitalWrite(params->pins_2[2], LOW);

}

void backward( int speed )
{
    pwmWrite(params->pins_1[0], speed);
    pwmWrite(params->pins_2[0], speed);
    digitalWrite(params->pins_1[1], LOW);
    digitalWrite(params->pins_2[1], LOW);
    digitalWrite(params->pins_1[2], HIGH);
    digitalWrite(params->pins_2[2], HIGH);
}

void hardLeft( int speed )
{
    pwmWrite(params->pins_1[0], speed);
    pwmWrite(params->pins_2[0], speed);
    digitalWrite(params->pins_1[1], LOW);
    digitalWrite(params->pins_2[1], HIGH);
    digitalWrite(params->pins_1[2], HIGH);
    digitalWrite(params->pins_2[2], LOW);
}

void hardRight( int speed )
{
    pwmWrite(params->pins_1[0], speed);
    pwmWrite(params->pins_2[0], speed);
    digitalWrite(params->pins_1[1], HIGH);
    digitalWrite(params->pins_2[1], LOW);
    digitalWrite(params->pins_1[2], LOW);
    digitalWrite(params->pins_2[2], HIGH);
}


void motor_init ()
{
    pinMode(params->pins_1[0], PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(384);
    pwmSetRange(1000); // was 1000 in example?
    pinMode(params->pins_1[1], OUTPUT);
    pinMode(params->pins_1[2], OUTPUT);
    
    pinMode(params->pins_2[0], PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(384);
    pwmSetRange(1000); // was 1000 in example?
    pinMode(params->pins_1[1], OUTPUT);
    pinMode(params->pins_1[2], OUTPUT);
    
    
    
    
    
}



