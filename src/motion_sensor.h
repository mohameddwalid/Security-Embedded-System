// pir_sensor.h
#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <stdbool.h>  // Include for bool type


// Function to initialize the PIR sensor
void initMotionSensor(int pin);

// Function to read the PIR sensor's state
bool isMotionDetected();

#endif
