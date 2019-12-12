#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "../../src/headers/pins.h"


int MAX_SPEED = 100;

void motor_init();
void set_motor_1( int forward, int backward, int speed);
void set_motor_2( int forward, int backward, int speed);


void set_motor_1( int forward, int backward, int speed)
{
    //printf("MOTOR_1: %d %d %d\n", forward, backward, speed);
    if(speed > MAX_SPEED) speed = MAX_SPEED;
    softPwmWrite(MOTOR_1_PWM, speed);
    digitalWrite(MOTOR_1_F, forward);
    digitalWrite(MOTOR_1_R, backward);
}

void set_motor_2( int forward, int backward, int speed)
{
    //printf("MOTOR_2: %d %d %d\n", forward, backward, speed);
    if(speed > MAX_SPEED) speed = MAX_SPEED;
    softPwmWrite(MOTOR_2_PWM, speed);
    digitalWrite(MOTOR_2_F, forward);
    digitalWrite(MOTOR_2_R, backward);

}

void motor_init ()
{
    
    printf("MOTOR_1: %d %d %d\n", MOTOR_1_F, MOTOR_1_R, MOTOR_1_PWM);
    printf("MOTOR_2: %d %d %d\n", MOTOR_2_F, MOTOR_2_R, MOTOR_2_PWM);
    pinMode(MOTOR_1_F, OUTPUT);
    pinMode(MOTOR_1_R, OUTPUT);
    pinMode(MOTOR_1_PWM, PWM_OUTPUT);
    
    pinMode(MOTOR_2_F, OUTPUT);
    pinMode(MOTOR_2_R, OUTPUT);
    pinMode(MOTOR_2_PWM, PWM_OUTPUT);
    
    softPwmCreate(MOTOR_1_PWM, 0, 100);
    softPwmCreate(MOTOR_2_PWM, 0, 100);
}



