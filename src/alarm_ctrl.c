#include "alarm_ctrl.h"
#include "pico/stdlib.h"


int alarmPin;

void initAlarm(int pin) {
    alarmPin = pin;
    gpio_init(alarmPin);
    gpio_set_dir(alarmPin, GPIO_OUT);
        gpio_put(alarmPin, 0);


}

void alarmturnOn() {
    gpio_put(alarmPin, 1);
}
void alarmturnOff() {
    gpio_put(alarmPin, 0);
}