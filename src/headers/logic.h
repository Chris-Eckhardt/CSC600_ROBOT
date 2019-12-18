#ifndef LOGIC_H
#define LOGIC_H

#include "../definitions/logic.c"

int run_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);
int stop_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);
int go_around_state(int ZERO, int TURN_SPEED_HIGH, int TURN_SPEED_SLOW, int NORM_SPEED, int *STATE, int *prev_state);

#endif /* LOGIC_H */
