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
*   Disclaimer : 
*   If product becomes sentient, 
*   please consult user manual.
*
**************************************/
/*********************************
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 ********************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include "./util/arguments.h"
#include "./sensors/sensor.h"
#include "./util/etc.h"
#include "./motors/motors.h"

/*********************************
* PIN DEFINITIONS
 ********************************/
 
#define PIN_IR_1 23
#define PIN_IR_2 24
#define PIN_IR_3 6
#define PIN_LINE_1 7
#define PIN_LINE_2 8
#define PIN_SONAR_TRIGGER 9
#define PIN_SONAR_ECHO 10
#define MOTOR_1_A 12
#define MOTOR_1_B 12
#define MOTOR_2_A 12
#define MOTOR_2_B 12
#define PIN_ON_OFF 11
#define NUM_OF_THREADS 9

/*********************************
 * Sensor Input Variables
 ********************************/
 
volatile int IR_1 = 0;
volatile int IR_2 = 0;
volatile int IR_3 = 0;
volatile int LINE_1 = 0;
volatile int LINE_2 = 0;
volatile int LINE_3 = 0;
volatile int LINE_4 = 0;
volatile int SONAR = 0;
volatile int ON_OFF_BUTTON = 0;

/*********************************
 * Uninitialized Variables
 ********************************/
 
pthread_t pid;
static struct Thread_Argument * args;

/*********************************
 * Function Prototypes
 ********************************/
 
void exit_handler();
void run();

/*********************************
 * MAIN
 ********************************/
 
int main()
{
    /*************************** CNTL_C SIGNAL HANDLER **********************/
    signal(SIGINT, exit_handler);
    
    /********************** MALLOC SPACE FOR ARGUMENT STRUCTS *********************/
    if( (args = malloc(sizeof(struct Thread_Argument) * NUM_OF_THREADS)) == NULL) {
        printf("malloc fail\n");
        exit(1);
    }
    
    /*************************** ASSIGN ARGUMENT VALUES **********************/
    args[0].pin_1 = PIN_IR_1;
    args[0].pin_2 = PIN_IR_2;
    args[0].ptr = &IR_1;
    
    /*************************** LAUNCH THREADS **********************/
    /*
    if(pthread_create(&pid, NULL, (void *)light_emitting_sensor, (void *)args[0]) != 0) {
        printf("pthread_create fail\n");
        exit(1);
    }
    */
    if(pthread_create(&pid, NULL, (void *)motor_init, (void *)&args[0]) != 0) {
        printf("pthread_create fail\n");
        exit(1);
    }
    
    /************* RUN ***************/
    run();
    /*********************************/
    
    return 0;
}

void run()
{
    while(1) {
        //printf( IR_1 ? "CLEAR\n" : "OBSTACLE\n" );
        delay(30);
    }
}

/*********************************
 * SIGNAL EXIT HANDLER
 ********************************/
 
void exit_handler() {
    pthread_cancel(pid);
    free(args);
    args = NULL;
    printf("\nexiting...\n");
    exit(0);
}
