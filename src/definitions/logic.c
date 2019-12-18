#include <stdio.h>
#include <stdlib.h>
#include "../headers/test.h"
#include "../headers/data.h"
#include "../headers/sensor.h"
#include "../headers/motors.h"

#define SONAR_MIN_LIMIT 30.f

int run_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);
int stop_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);
int go_around_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);


int counter = 0, go_around = 0, has_seen_line = 0;


int run_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state)
{
		
		if(SONAR <= SONAR_MIN_LIMIT)
        {
            //printf("STOP YOU FOOL\n");
             set_motor_RIGHT(1, 0, ZERO);
             set_motor_LEFT(1,0,ZERO);
             counter = 0;
             has_seen_line = 0;
             *STATE = 1;
             return -1;
        }
              
        if(LINE_LEFT == 0) // RIGHT TURN
        {
            //printf("RIGHT TURN");
            set_motor_RIGHT(1,0,ZERO);
			set_motor_LEFT(1,0,TURN_SPEED_HIGH);
        }
        else if(LINE_RIGHT == 0) // LEFT TURN
        {
            //printf("LEFT TURN");
            set_motor_RIGHT(1,0,TURN_SPEED_HIGH);
            set_motor_LEFT(1,0, ZERO);
        }
        else if(LINE_CENTER == 0)
		{
            //printf("FORWARD ONTO DAWN");
            set_motor_RIGHT(1,0,NORM_SPEED);
            set_motor_LEFT(1,0,NORM_SPEED);
         }
         else
         {
            set_motor_RIGHT(0,1,30);
            set_motor_LEFT(1,0,30);		 
		 }
       
         return 0;
}

int stop_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state)
{
	// check if obstacle is gone
            if(SONAR > SONAR_MIN_LIMIT)
            {
                *STATE = 0;
                return -1;
            }
            // check if if state just changed, if not counter ++
            if(*STATE == *prev_state)
            {
                counter++;
            }
            
            // if counter > 12000, STATE = GO AROUND
            if(counter > 300)
            {
                *STATE = 2;
                return -1;
            }
            return 0;
}

int go_around_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state)
{
	       // turn 90 deg right
           set_motor_RIGHT(0,1, TURN_SPEED_HIGH);
           set_motor_LEFT(1,0,TURN_SPEED_HIGH);
           delay(10);
           
			// drive straight
            set_motor_RIGHT(1,0, NORM_SPEED);
            set_motor_LEFT(1,0, NORM_SPEED);
            delay(10);
           
            // turn 90 left
			set_motor_RIGHT(1,0,TURN_SPEED_HIGH);
            set_motor_LEFT(0,1,TURN_SPEED_HIGH);
            delay(10);
            
            // go 2 feet
            set_motor_RIGHT(1,0,NORM_SPEED);
            set_motor_LEFT(1,0,NORM_SPEED);
            delay(10);
          
            // turn 90 left
            set_motor_RIGHT(1,0,TURN_SPEED_HIGH);
            set_motor_LEFT(0,1,TURN_SPEED_HIGH);
            delay(10);
           
            // go until lines == 0, go 7-8 inches
            set_motor_RIGHT(1,0,NORM_SPEED);
            set_motor_LEFT(1,0,NORM_SPEED);
            delay(10);
           
            // turn right until right line sees line then does not

             if(LINE_LEFT == 1)
             {
                set_motor_RIGHT(0,1,TURN_SPEED_HIGH);
                set_motor_LEFT(1,0,TURN_SPEED_HIGH);
             }
             if(LINE_LEFT == 1 && has_seen_line)
             {
                 *STATE = 0;
				  printf("CHECK\n");
                  getchar();
                  return -1;
              }
              else if(LINE_LEFT == 0 && !has_seen_line)
              {
                  has_seen_line = 1;
              }
              else
			  {
                 // DO NOTHING
              }
                
            
       return 0;
}

