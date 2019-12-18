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

#define RUN 0
#define STOP 1
#define GO_AROUND 2
#define NORM_SPEED 30
#define TURN_SPEED_SLOW 20
#define TURN_SPEED_HIGH 30
#define TURBO 50
#define ZERO 0

/*********************************
 * ADMIN: Variables
 ********************************/
int motor_speed_right = 0;
int motor_speed_left = 0;
pthread_t pid;
int STATE;
int prev_state = 0;


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
    /* setup exit handler */
    signal(SIGINT, exit_handler);
    
    /* init wiring pi */
    if(wiringPiSetup() == -1) {
        printf("setup wiringPi failed!");
        exit(1);
    }
    
    /* init sensors */
    sensor_init();
    motor_init();
    
    /* wait for start button */
    while(1) {
        printf("IR LEFT:\n", IR_LEFT);
        if(!digitalRead(PIN_IR_LEFT)) {
            run();
        }
        delay(50);
    }
    
    /* exit program */
    return 0;
}

/*********************************
 * MAIN: RUN
 ********************************/

void run()
{
    
    STATE = RUN;
    // mobility_test(); // TEST

    while(1)
    {
        get_sensor_data();
        printf("STATE: %d | TILT: %d | COUNTER: %d | HAS_SEEN: %d | LINE_R: %d | LINE_L: %d | SONAR: %f | IR_R: %d | IR_L: %d |\n",STATE, TILT, counter, has_seen_line, LINE_RIGHT, LINE_LEFT, SONAR, IR_RIGHT, IR_LEFT); // TEST
                
        if ( STATE == RUN ) 
        {
            if (run_state(ZERO, TURN_SPEED_HIGH, TURN_SPEED_SLOW, NORM_SPEED, &STATE, &prev_state) < 0) continue;
        }
        
        if ( STATE == STOP )
        {
            if (stop_state(ZERO, TURN_SPEED_HIGH, TURN_SPEED_SLOW, NORM_SPEED, &STATE, &prev_state) < 0) continue;
        }
        
        if ( STATE == GO_AROUND )
        {
            if (go_around_state(ZERO, TURN_SPEED_HIGH, TURN_SPEED_SLOW, NORM_SPEED, &STATE, &prev_state) < 0) continue;
       }
      
      prev_state = STATE;
    
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
    digitalWrite(PIN_IR_RIGHT, LOW);
    digitalWrite(PIN_IR_LEFT, LOW);
    digitalWrite(PIN_LINE_RIGHT, LOW);
    digitalWrite(PIN_LINE_LEFT, LOW);
    digitalWrite(PIN_SONAR_TRIGGER, LOW);

    printf("***** Resetting pin modes   *****\n");
    pinMode(PIN_IR_RIGHT, INPUT);
    pinMode(PIN_IR_LEFT, INPUT);
    pinMode(PIN_LINE_RIGHT, INPUT);
    pinMode(PIN_LINE_LEFT, INPUT);
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
