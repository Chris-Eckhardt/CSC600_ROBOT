#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "pthread.h"

void get_sensor_data();
void init_sensors();
float sonar();

void get_sensor_data()
{

    LINE_1 = digitalRead(PIN_LINE_1);
    LINE_2 = digitalRead(PIN_LINE_2);
    IR_1 = digitalRead(PIN_IR_1);
    LINE_2 = digitalRead(PIN_IR_2);
    //SONAR = sonar(); // If you dont have the hardware attached this will cause a hang.
    
}

void sensor_init()
{
    pinMode(PIN_LINE_1, INPUT);
    pinMode(PIN_LINE_2, INPUT);
    pinMode(PIN_IR_1, INPUT);
    pinMode(PIN_IR_2, INPUT);
    pinMode(PIN_SONAR_TRIGGER, INPUT);
    pinMode(PIN_SONAR_ECHO, OUTPUT);
    digitalWrite(PIN_SONAR_TRIGGER, LOW);
}

float sonar() {
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
	float distance;
	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delay(20);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	while(!(digitalRead(PIN_SONAR_ECHO) == 1));
	gettimeofday(&tv1, NULL);
	while(!(digitalRead(PIN_SONAR_ECHO) == 0));
	gettimeofday(&tv2, NULL);
	time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
	time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;
	distance = (float)(time2 - time1) / 1000000 * 34000 / 2;
	return distance;
}

