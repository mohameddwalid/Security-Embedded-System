
#include "proximity_sensor.h"
#include "hardware/gpio.h"  // Include the GPIO library for RP2040 (or equivalent for your board)

// Variable to store the PIR sensor pin
int IRsensorPin;

// Function to initialize the PIR sensor
void initProximitySensor(int pin) {
    IRsensorPin = pin;
    gpio_init(IRsensorPin);            
    gpio_set_dir(IRsensorPin, GPIO_IN); 
}

// Function to check if motion is detected
bool objectDetected() {
    return !gpio_get(IRsensorPin); 
}
