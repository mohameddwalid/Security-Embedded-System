#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#include <stdint.h>  // Include for uint16_t type


#include <stdbool.h>  // Include for bool type


// Function to initialize the sound sensor
void initSoundSensor(int pin);

// Function to read the analog value from the sound sensor
uint16_t readSoundSensor();

// Function to check if the sound sensor detects sound over a threshold
bool isSoundDetected(uint16_t threshold);

#endif // SOUND_SENSOR_H
