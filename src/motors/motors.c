#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "../util/arguments.h"

int MAX_SPEED = 100;

void motor_init();
void set_motor_1( int forward, int backward, int speed);
void set_motor_2( int forward, int backward, int speed);


void set_motor_1( int forward, int backward, int speed)
{
    if(speed > 100) speed = 100; // SLOW DOWN THERE, TURBO
    digitalWrite(MOTOR_1_F, forward);
    digitalWrite(MOTOR_1_R, backward);
    softPwmWrite(MOTOR_1_PWM, speed);
}

void set_motor_2( int forward, int backward, int speed)
{
    if(speed > 100) speed = 100; // SLOW DOWN THERE, TURBO
    digitalWrite(MOTOR_2_F, forward);
    digitalWrite(MOTOR_2_R, backward);
    softPwmWrite(MOTOR_2_PWM, speed);
}

void motor_init ()
{
    pinMode(MOTOR_1_F, OUTPUT);
    pinMode(MOTOR_1_R, OUTPUT);
    pinMode(MOTOR_1_PWM, PWM_OUTPUT);
    
    pinMode(MOTOR_2_F, OUTPUT);
    pinMode(MOTOR_2_R, OUTPUT);
    pinMode(MOTOR_2_PWM, PWM_OUTPUT);
    
    softPwmCreate(MOTOR_1_PWM, 0, 100);
    softPwmCreate(MOTOR_2_PWM, 0, 100);
}



