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
#include "./util/arguments.h"
#include "./util/pins.h"
#include "./util/test.h"
#include "./util/data.h"
#include "./logic/logic.h"
#include "./sensors/sensor.h"
#include "./motors/motors.h"

/*********************************
 * PINS: PIN ARRAYS
 ********************************/
int sonar_pins[] = {PIN_SONAR_TRIGGER, PIN_SONAR_ECHO};
int ir_1_pin[] = {PIN_IR_1};
int ir_2_pin[] = {PIN_IR_2};
int ir_3_pin[] = {PIN_IR_3};
int line_1_pin[] = {PIN_LINE_1};
int line_2_pin[] = {PIN_LINE_2};
int line_3_pin[] = {PIN_LINE_3};
int line_4_pin[] = {PIN_LINE_4};
int pin_on_off[] = {PIN_ON_OFF};

/*********************************
 * ADMIN: Variables
 ********************************/
pthread_t sonar_pid;
pthread_t ir_1_pid;
pthread_t ir_2_pid;
pthread_t ir_3_pid;
pthread_t line_1_pid;
pthread_t line_2_pid;
pthread_t line_3_pid;
pthread_t line_4_pid;

struct Thread_Argument * args;
int motor_speed_right = 0;
int motor_speed_left = 0;
int limiter = 100;

/*********************************
 * ADMIN: Function Prototypes
 ********************************/
 
void exit_handler();
void init();
void set_thread_args();
void run();

/*********************************
 * MAIN: MAIN
 ********************************/
 
int main()
{
    signal(SIGINT, exit_handler);
    init();
    run();
    return 0;
}

/*********************************
 * MAIN: RUN
 ********************************/

void run()
{
    
    mobility_test();
    
    while(1) 
    {
        // proximity check, set limiter
        if(SONAR < 100.) limiter = 60;
        else if (SONAR < 50) limiter = 30;
        else limiter = 100;
        
        if(SONAR < 15 && IR_1 == 1 && IR_2 == 1)
        {
            backtrack();
            continue;
        } 
        /* Clear right */
        else if(SONAR < 15 && IR_1 == 1 && IR_2 == 0)
        {
            pivot_right();
            continue;
        }
        /* Clear left */
        else if(SONAR < 15 && IR_1 == 1 && IR_2 == 0)
        {
            pivot_left();
            continue;
        } 
        /* Clear right and left */
        else if(SONAR < 15 && IR_1 == 0 && IR_2 == 0)
        {
            pivot_left(); // default left
            continue;
        } 
        else
        {
            pathfind();
        }
        
        
    }
}

/*********************************
 * INIT: MALLOC AND THREAD SPAWN
 ********************************/

void init()
{
    

    IR_1 = IR_2 = IR_3 = 0;
    LINE_1 =LINE_2 = LINE_3 = LINE_4 = 0;
    SONAR = 0;
    ON_OFF_BUTTON = 0;

    
    if(wiringPiSetup() == -1) {
        printf("setup wiringPi failed!");
        exit(1);
    }
    
    if( (args = malloc( sizeof(struct Thread_Argument)* NUM_OF_THREADS) ) == NULL )
    {
        printf("\n***** malloc fail @ init *****\n");
        exit(1);
    }

    set_thread_args();

    // COMMENT THESE OUT UNTIL PROPER GPIO PIN ASSIGNMENT 
    //pthread_create( &sonar_pid, NULL, (void *) sonar_thread, (void *) &args[1]);
    //pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[2]);
    //pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[3]);
    //pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[4]);
    //pthread_create( &line_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[5]);
    //pthread_create( &line_2_pid, NULL, (void *) light_emitting_thread, (void *) &args[6]);
    //pthread_create( &line_3_pid, NULL, (void *) light_emitting_thread, (void *) &args[7]);
    //pthread_create( &line_4_pid, NULL, (void *) light_emitting_thread, (void *) &args[8]);
}

/*********************************
 * HELPER: SET THREAD ARGUMENTS
 ********************************/

void set_thread_args()
{
    int i = 0;
    /* SONAR ARGS */
    args[i].pid = &sonar_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = sonar_pins;
    args[i].ptr = NULL;
    args[i].sonar_ptr = &SONAR;
    i++;
    /* IR 1 */
    args[i].pid = &ir_1_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_1_pin;
    args[i].ptr = &IR_1;
    args[i].sonar_ptr = NULL;
    i++;
    /* IR 2 */
    args[i].pid = &ir_2_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_2_pin;
    args[i].ptr = &IR_2;
    args[i].sonar_ptr = NULL;
    i++;
    /* IR 3 */
    args[i].pid = &ir_3_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_3_pin;
    args[i].ptr = &IR_3;
    args[i].sonar_ptr = NULL;
    i++;
    /* LINE SENSOR 1 */
    args[i].pid = &line_1_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_1_pin;
    args[i].ptr = &LINE_1;
    args[i].sonar_ptr = NULL;
    i++;
    /* LINE SENSOR 2 */
    args[i].pid = &line_2_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_2_pin;
    args[i].ptr = &LINE_2;
    args[i].sonar_ptr = NULL;
    i++;
    /* LINE SENSOR 3 */
    args[i].pid = &line_3_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_3_pin;
    args[i].ptr = &LINE_3;
    args[i].sonar_ptr = NULL;
    i++;
    /* LINE SENSOR 4 */
    args[i].pid = &line_4_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_4_pin;
    args[i].ptr = &LINE_4;
    args[i].sonar_ptr = NULL;
    
}

/*********************************
 * SIGNAL: SIGNAL EXIT HANDLER
 ********************************/
 
void exit_handler() {

    printf("\n*********************************\n");
    printf("*****       Exiting...      *****\n");
    printf("***** Shutting down threads *****\n");
    for(int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_cancel(*args[i].pid);
    }
    printf("***** Zeroing out pins      *****\n");
    softPwmWrite(MOTOR_1_PWM, 0);
    softPwmWrite(MOTOR_2_PWM, 0);
    digitalWrite(MOTOR_1_F, LOW);
    digitalWrite(MOTOR_1_R, LOW);
    digitalWrite(MOTOR_2_F, LOW);
    digitalWrite(MOTOR_2_R, LOW);
    digitalWrite(PIN_IR_1, LOW);
    digitalWrite(PIN_IR_2, LOW);
    digitalWrite(PIN_IR_3, LOW);
    digitalWrite(PIN_LINE_1, LOW);
    digitalWrite(PIN_LINE_2, LOW);
    digitalWrite(PIN_LINE_3, LOW);
    digitalWrite(PIN_LINE_4, LOW);
    digitalWrite(PIN_SONAR_TRIGGER, LOW);

    printf("***** Resetting pin modes   *****\n");
    pinMode(PIN_IR_1, INPUT);
    pinMode(PIN_IR_2, INPUT);
    pinMode(PIN_IR_3, INPUT);
    pinMode(PIN_LINE_1, INPUT);
    pinMode(PIN_LINE_2, INPUT);
    pinMode(PIN_LINE_3, INPUT);
    pinMode(PIN_LINE_4, INPUT);
    pinMode(MOTOR_1_F, INPUT);
    pinMode(MOTOR_1_R, INPUT);
    pinMode(MOTOR_1_PWM, INPUT);
    pinMode(MOTOR_2_F, INPUT);
    pinMode(MOTOR_2_R, INPUT);
    pinMode(MOTOR_2_PWM, INPUT);
    pinMode(PIN_SONAR_ECHO, INPUT);
    pinMode(PIN_SONAR_TRIGGER, INPUT);
    
    printf("***** Freeing resources     *****\n");
    free(args);
    args = NULL;
    printf("***** shutdown complete     *****\n");
    printf("*********************************\n");
    exit(0);
}
