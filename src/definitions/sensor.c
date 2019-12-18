#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include "pthread.h"

void * sensor_thread (void * arg );
void get_sensor_data();
void sensor_init();
float sonar();

float temp;
int timeout = 12000;

void * sensor_thread ( void * args )
{
    while(1)
    {
        get_sensor_data();
        //delay(20);
    }
}

void get_sensor_data()
{
    LINE_RIGHT = digitalRead(PIN_LINE_RIGHT);
    LINE_LEFT = digitalRead(PIN_LINE_LEFT);
    LINE_CENTER = digitalRead(PIN_LINE_CENTER);
    TILT = digitalRead(PIN_TILT);
    //IR_RIGHT = digitalRead(PIN_IR_RIGHT);
    IR_LEFT = digitalRead(PIN_IR_LEFT);
    SONAR = sonar(); // If you dont have the hardware attached this will cause a hang.
}

void sensor_init()
{
    pinMode(PIN_TILT, INPUT);
    pinMode(PIN_LINE_CENTER, INPUT);
    pinMode(PIN_LINE_RIGHT, INPUT);
    pinMode(PIN_LINE_LEFT, INPUT);
    //pinMode(PIN_IR_RIGHT, INPUT);
    pinMode(PIN_IR_LEFT, INPUT);
    pinMode(PIN_SONAR_TRIGGER, OUTPUT);
    pinMode(PIN_SONAR_ECHO, INPUT);
    digitalWrite(PIN_SONAR_TRIGGER, LOW);
}

float sonar()
{
    	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delay(10);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	
	while(!digitalRead(PIN_SONAR_ECHO));
	
	long startTime = micros();
	while(digitalRead(PIN_SONAR_ECHO) && (micros()-startTime)<timeout);
	long travelTime = micros() - startTime;
	int distance = travelTime / 58;
	
	return distance;

}

