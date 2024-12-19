

#ifndef SERVO_CTRL_H
#define SERVO_CTRL_H

#include "pico/stdlib.h"

 
#define SERVO_MIN_PULSE_WIDTH 500   // Minimum pulse width in microseconds for 0°
#define SERVO_MAX_PULSE_WIDTH 2500  // Maximum pulse width in microseconds for 180°
#define SERVO_FREQUENCY 50          // Servo frequency for SG90 (50 Hz)

void initServo(int pin);
void setServoAngle(float angle);

#endif // SERVO_CONTROL_H