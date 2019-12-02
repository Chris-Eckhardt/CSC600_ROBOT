#ifndef ARGUMENTS
#define ARGUMENTS

struct Thread_Argument
{ 
    int pin_1;
    int pin_2;
    volatile int * ptr;
};

struct Motor_Argument
{
    int pin_M_1A;
    int pin_M_1B;
    int pin_M_1C;
    int pin_M_1D;
    int pin_M_1E;
    int pin_M_1F;

    int pin_M_2A;
    int pin_M_2B;
    int pin_M_2C;
    int pin_M_2D;
    int pin_M_2E;
    int pin_M_2F;
};

#endif
