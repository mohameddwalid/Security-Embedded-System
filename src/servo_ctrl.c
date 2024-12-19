
#include "servo_ctrl.h"
#include "hardware/pwm.h"

int servoPin;

// Function to initialize PWM for servo control
void initServo(int pin) {

    servoPin = pin;

    // Set the GPIO function for PWM
    gpio_set_function(servoPin, GPIO_FUNC_PWM);

    // Get PWM slice number for the chosen pin
    uint slice_num = pwm_gpio_to_slice_num(servoPin);

    // Configure PWM for 50 Hz (20 ms period)
    pwm_set_wrap(slice_num, 20000);  // 20 ms period (for 50 Hz)
    pwm_set_clkdiv(slice_num, 125.0); // Adjust clock divider to get 20 ms period with 125 MHz clock

    // Enable PWM output
    pwm_set_enabled(slice_num, true);
}

// Function to set servo position based on angle (0° to 180°)
void setServoAngle(float angle) {
    // Clamp the angle between 0 and 180
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    // Calculate the pulse width for the given angle
    uint16_t pulse_width = SERVO_MIN_PULSE_WIDTH + (angle / 180.0) * (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH);

    // Set the PWM duty cycle to the calculated pulse width
    uint slice_num = pwm_gpio_to_slice_num(servoPin);
    pwm_set_gpio_level(servoPin, pulse_width);
}