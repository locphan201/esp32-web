#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Motor pin assignments
#define FL_DIR_A 14
#define FL_DIR_B 15
#define FL_PWM   4

#define FR_DIR_A 16
#define FR_DIR_B 17
#define FR_PWM   5

#define RL_DIR_A 18
#define RL_DIR_B 19
#define RL_PWM   21

#define RR_DIR_A 22
#define RR_DIR_B 23
#define RR_PWM   25

// Base speed (0-255)
extern int baseSpeed;

void initMotors();
void stopAllMotors();
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void rotateLeft();
void rotateRight();

#endif
