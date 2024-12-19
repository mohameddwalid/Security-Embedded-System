#include "sound_sensor.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int soundSensorPin;

void initSoundSensor(int pin) {
    soundSensorPin = pin;

    // Initialize the ADC system
    adc_init();

    // Initialize GPIO 26 for analog input (ADC 0)
    adc_gpio_init(soundSensorPin);

    // Select ADC input 0 (GPIO 26 = ADC 0)
    adc_select_input(soundSensorPin - 26);
}

uint16_t readSoundSensor() {
    // Read the ADC value (12-bit resolution)
    return adc_read();
}

bool isSoundDetected(uint16_t threshold) {
    // Compare ADC value with the threshold
    return readSoundSensor() > threshold;
}
