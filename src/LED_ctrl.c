#include "LED_ctrl.h"
#include "hardware/gpio.h"  // Include the GPIO library for RP2040 (or equivalent for your board)


// int LEDPin;

void initLED(int pin) {
    // LEDPin = pin;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void ledturnOn(int pin) {
    gpio_put(pin, 1);
}
void ledturnOff(int pin) {
    gpio_put(pin, 0);
}