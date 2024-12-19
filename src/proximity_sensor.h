
#ifndef PROXIMITY_SENSOR_H
#define PROXIMITY_SENSOR_H

#include <stdbool.h>  // Include for bool type

// Function to initialize the PIR sensor
void initProximitySensor(int pin);

// Function to read the PIR sensor's state
bool objectDetected();

#endif
