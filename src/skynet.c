/**************************************
*  _____ _   ____   ___   _  _____ _____ 
* /  ___| | / /\ \ / / \ | ||  ___|_   _|
* \ `--.| |/ /  \ V /|  \| || |__   | |  
*  `--. \    \   \ / | . ` ||  __|  | |  
* /\__/ / |\  \  | | | |\  || |___  | |  
* \____/\_| \_/  \_/ \_| \_/\____/  \_/ 
*
*       COMMAND & CONTROL MODULE
*
**************************************/
/*********************************
 * 
 * DESCRIPTION: description goes here
 * 
 * BUILD: gcc -pthread -lwiringPi -o skynet skynet.c
 * 
 * EXECUTE: ./skynet
 * 
 ********************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <wiringPi.h>
#include "./headers/pins.h"
#include "./headers/test.h"
#include "./headers/data.h"
#include "./headers/logic.h"
#include "./headers/sensor.h"
#include "./headers/motors.h"

/*********************************
 * ADMIN: Variables
 ********************************/
int motor_speed_right = 0;
int motor_speed_left = 0;
int limiter = 100;

/*********************************
 * ADMIN: Function Prototypes
 ********************************/
 
void exit_handler();
void run();

/*********************************
 * MAIN: MAIN
 ********************************/
 
int main()
{
    signal(SIGINT, exit_handler);

    if(wiringPiSetup() == -1) {
        printf("setup wiringPi failed!");
        exit(1);
    }
    
    sensor_init();
    motor_init();
    
    run();
    
    return 0;
}

/*********************************
 * MAIN: RUN
 ********************************/

void run()
{

    //mobility_test();

    for(;;)
    {
        get_sensor_data();
        printf("        | LINE_1: %d | LINE_2: %d | SONAR: %f |\n", LINE_1, LINE_2, SONAR); // TEST
        /*
        if(LINE_1 == 1 && LINE_2 == 0)
        {
            printf("LINE_1\n");
            //set_motor_1(0,0,0);
        }
        else if(LINE_2 == 1 && LINE_1 == 0)
        {
            printf("LINE_2\n");
            //set_motor_2(0,0,0);
        }
        else
        {
            printf("GOING STRAIGHT\n");
            set_motor_1(1,0,50);
            set_motor_2(1,0,50);
        }*/
        
        delay(30);
        
        
    }
}

/*********************************
 * SIGNAL: SIGNAL EXIT HANDLER
 ********************************/
 
void exit_handler() {

    printf("\n*********************************\n");
    printf("*****       Exiting...      *****\n");
    printf("***** Zeroing out pins      *****\n");
    softPwmWrite(MOTOR_1_PWM, 0);
    softPwmWrite(MOTOR_2_PWM, 0);
    digitalWrite(MOTOR_1_F, LOW);
    digitalWrite(MOTOR_1_R, LOW);
    digitalWrite(MOTOR_2_F, LOW);
    digitalWrite(MOTOR_2_R, LOW);
    digitalWrite(PIN_IR_1, LOW);
    digitalWrite(PIN_IR_2, LOW);
    digitalWrite(PIN_LINE_1, LOW);
    digitalWrite(PIN_LINE_2, LOW);
    digitalWrite(PIN_SONAR_TRIGGER, LOW);

    printf("***** Resetting pin modes   *****\n");
    pinMode(PIN_IR_1, INPUT);
    pinMode(PIN_IR_2, INPUT);
    pinMode(PIN_LINE_1, INPUT);
    pinMode(PIN_LINE_2, INPUT);
    pinMode(MOTOR_1_F, INPUT);
    pinMode(MOTOR_1_R, INPUT);
    pinMode(MOTOR_1_PWM, INPUT);
    pinMode(MOTOR_2_F, INPUT);
    pinMode(MOTOR_2_R, INPUT);
    pinMode(MOTOR_2_PWM, INPUT);
    pinMode(PIN_SONAR_ECHO, INPUT);
    pinMode(PIN_SONAR_TRIGGER, INPUT);
    
    printf("***** shutdown complete     *****\n");
    printf("*********************************\n");
    exit(0);
}
