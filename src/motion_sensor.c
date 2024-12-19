#include "motion_sensor.h"
#include "hardware/gpio.h"  // Include the GPIO library for RP2040 (or equivalent for your board)

int pirSensorPin;

void initMotionSensor(int pin) {
    pirSensorPin = pin;
    gpio_init(pirSensorPin);            
    gpio_set_dir(pirSensorPin, GPIO_IN); 
}

bool isMotionDetected() {
    return gpio_get(pirSensorPin); 
    
}
