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
#include "./sensors/sensor.h"
#include "./motors/motors.h"

/*********************************
* PINS: PIN DEFINITIONS
 ********************************/
 
#define PIN_IR_1 23
#define PIN_IR_2 24
#define PIN_IR_3 6
#define PIN_LINE_1 7
#define PIN_LINE_2 8
#define PIN_LINE_3 7
#define PIN_LINE_4 8
#define PIN_SONAR_TRIGGER 9
#define PIN_SONAR_ECHO 10
#define MOTOR_1_A 32
#define MOTOR_1_B 24
#define MOTOR_1_C 26
#define MOTOR_2_A 19
#define MOTOR_2_B 21
#define MOTOR_2_C 23
#define PIN_ON_OFF 11
#define NUM_OF_THREADS 9

/*********************************
 * DATA: Sensor Input Variables
 ********************************/
 
volatile int IR_1 = 0;
volatile int IR_2 = 0;
volatile int IR_3 = 0;
volatile int LINE_1 = 0;
volatile int LINE_2 = 0;
volatile int LINE_3 = 0;
volatile int LINE_4 = 0;
volatile float SONAR = 0;
volatile int ON_OFF_BUTTON = 0;

/*********************************
 * PINS: PIN ARRAYS
 ********************************/

int motor_1_pins[] = {MOTOR_1_A, MOTOR_1_B, MOTOR_1_C};
int motor_2_pins[] = {MOTOR_2_A, MOTOR_2_B, MOTOR_2_C};
int sonar_pins[] = {PIN_SONAR_TRIGGER, PIN_SONAR_ECHO};
int ir_1_pin[] = {PIN_IR_1};
int ir_2_pin[] = {PIN_IR_2};
int ir_3_pin[] = {PIN_IR_3};
int line_1_pin[] = {PIN_LINE_1};
int line_2_pin[] = {PIN_LINE_2};
int line_3_pin[] = {PIN_LINE_3};
int line_4_pin[] = {PIN_LINE_4};
int pin_on_off = (PIN_ON_OFF);

/*********************************
 * ADMIN: Uninitialized Variables
 ********************************/
 
pthread_t motor_pid;
pthread_t sonar_pid;
pthread_t ir_1_pid;
pthread_t ir_2_pid;
pthread_t ir_3_pid;
pthread_t line_1_pid;
pthread_t line_2_pid;
pthread_t line_3_pid;
pthread_t line_4_pid;

struct Thread_Argument * args;

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
    while(1) 
    {

        printf("running...\n");
        delay(30);
    }
}

/*********************************
 * INIT: MALLOC AND THREAD SPAWN
 ********************************/

void init()
{
    
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

    pthread_create( &motor_pid, NULL, (void *) motor_thread, (void *) &args[0]);
    pthread_create( &sonar_pid, NULL, (void *) sonar_thread, (void *) &args[1]);
    pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[2]);
    pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[3]);
    pthread_create( &ir_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[4]);
    pthread_create( &line_1_pid, NULL, (void *) light_emitting_thread, (void *) &args[5]);
    pthread_create( &line_2_pid, NULL, (void *) light_emitting_thread, (void *) &args[6]);
    pthread_create( &line_3_pid, NULL, (void *) light_emitting_thread, (void *) &args[7]);
    pthread_create( &line_4_pid, NULL, (void *) light_emitting_thread, (void *) &args[8]);
}

/*********************************
 * HELPER: SET THREAD ARGUMENTS
 ********************************/

void set_thread_args()
{
    int i = 0;
    args[i].pid = &motor_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = motor_1_pins;
    args[i].pins_2 = motor_2_pins;
    args[i].ptr = NULL;
    i++;
    args[i].pid = &sonar_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = sonar_pins;
    args[i].pins_2 = NULL;
    args[i].ptr = NULL;
    args[i].sonar_ptr = &SONAR;
    i++;
    args[i].pid = &ir_1_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_1_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &IR_1;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &ir_2_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_2_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &IR_2;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &ir_3_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = ir_3_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &IR_3;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &line_1_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_1_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &LINE_1;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &line_2_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_2_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &LINE_2;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &line_3_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_3_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &LINE_3;
    args[i].sonar_ptr = NULL;
    i++;
    args[i].pid = &line_4_pid;
    args[i].thread_id = i+1;
    args[i].pins_1 = line_4_pin;
    args[i].pins_2 = NULL;
    args[i].ptr = &LINE_4;
    args[i].sonar_ptr = NULL;
}

/*********************************
 * SIGNAL: SIGNAL EXIT HANDLER
 ********************************/
 
void exit_handler() {
    printf("\n*****    exiting...     *****\n");
    for(int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_cancel(*args[i].pid);
        printf("thread %d of %d cancelled\n", args[i].thread_id, NUM_OF_THREADS);
    }
    free(args);
    args = NULL;
    printf("***** shutdown complete *****\n");
    exit(0);
}
