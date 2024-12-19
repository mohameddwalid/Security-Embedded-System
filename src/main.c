// #include <stdio.h>
// #include "pico/stdlib.h"

// #include "LED_ctrl.h"
// #include "motion_sensor.h"
// #include "alarm_ctrl.h"
// #include "proximity_sensor.h"
// #include "servo_ctrl.h"
// #include "sound_sensor.h"  // Include the sound sensor header

// int main() {
//     int pirSensorPin = 19;        // PIR sensor pin
//     int proximitySensorPin = 18;  // Proximity sensor pin
//     // int LEDPin = 20;              // LED pin

//     int LED1 = 15;
//     int LED2 = 16;
//     int LED3 = 17;
    


//     int alarmPin = 21;            // Alarm pin
//     int soundPin = 26;            // Sound sensor pin
//     int servoPin = 27;             // Servo motor pin


//     initServo(servoPin);
//     initAlarm(alarmPin);
//     initProximitySensor(proximitySensorPin);
//     initMotionSensor(pirSensorPin);
//     // initLED(LEDPin);
//     initLED(LED1);
//     initLED(LED2);
//     initLED(LED3);
//     initSoundSensor(soundPin);  // Initialize the sound sensor

//     // Initialize chosen serial port
//     stdio_init_all();

  
//     uint16_t moderateThreshold = 800;  // Threshold for moderate sound
//     uint16_t highThreshold = 1000;      // Threshold for high sound

// setServoAngle(0.0);
//     // Main loop
  
// int i =0;
// while (true) {


//      uint16_t soundValue = readSoundSensor();

//         if (soundValue < moderateThreshold) {
            
                
                
               
//                             // setServoAngle(0.0);

            
//             soundValue = readSoundSensor();
//         } else if (soundValue < highThreshold) {
//             // Moderate sound: Blink twice (same as no sound for now)
            
               
                
                
//                             // setServoAngle(0.0);

            
//             soundValue = readSoundSensor();
//         } else {
//             // // High sound: Blink five times
//             // for (int i = 0; i < 2; i++) {
//             //     ledturnOn(LED3);
//             //     sleep_ms(150);
//             //     ledturnOff(LED3);
//             //     sleep_ms(150);
//             // }
//             ledturnOn(LED1);
//             setServoAngle(90.0);
//                         alarmturnOn();


//             soundValue = readSoundSensor();
            
//         }



//         if(isMotionDetected ()){
            
//             ledturnOn(LED2);
//                         alarmturnOn();

//             setServoAngle(90.0);
          


         
//         }else{
//             // ledturnOff(LED1);
//             // ledturnOff(LED3);
//                         // setServoAngle(0.0);
//                         // alarmturnOff();

//         }

//         if(objectDetected()){
//             ledturnOn(LED2);
//             alarmturnOn();
           
//             setServoAngle(90.0);
           
//         }else{
//             // ledturnOff(LED2);
//             // alarmturnOff();
//             // ledturnOff(LED3);
//                         // setServoAngle(0.0);
//         }

        

//         // Move servo to 0 degrees
//         // if(i==0){
//         //     setServoAngle(0.0);
//         //     i=1;


//         // }else{
//         //     setServoAngle(90.0);

//         //     i=0;
//         // }
        
        
//         // }


// }
// }

#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"      // Include FreeRTOS headers
#include "task.h"          // Task-related APIs
#include "queue.h"

#include "LED_ctrl.h"
#include "motion_sensor.h"
#include "alarm_ctrl.h"
#include "proximity_sensor.h"
#include "servo_ctrl.h"
#include "sound_sensor.h"

// Define sensor and actuator pins
#define PIR_SENSOR_PIN 19
#define PROXIMITY_SENSOR_PIN 18
#define SOUND_SENSOR_PIN 26
#define LED1_PIN 15
#define LED2_PIN 16
#define LED3_PIN 17
#define ALARM_PIN 21
#define SERVO_PIN 27

// Thresholds for sound sensor
#define MODERATE_THRESHOLD 600
#define HIGH_THRESHOLD 1000

// Shared variables for concurrency
volatile int motionDetected = 0;
volatile int proximityDetected = 0;
volatile int soundDetected = 0;







// Task prototypes
void motionSensorTask(void *pvParameters);
void proximitySensorTask(void *pvParameters);
void soundSensorTask(void *pvParameters);
void ledAndAlarmControlTask(void *pvParameters);

// Hook for stack overflow
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("Stack overflow in task: %s\n", pcTaskName);
    while (1);  // Hang here for debugging
}

// Hook for malloc failure
void vApplicationMallocFailedHook(void) {
    printf("Malloc failed!\n");
    while (1);  // Hang here for debugging
}

int main() {
    // Initialize peripherals
    initServo(SERVO_PIN);
    initAlarm(ALARM_PIN);
    initLED(LED1_PIN);
    initLED(LED2_PIN);
    initLED(LED3_PIN);
    initMotionSensor(PIR_SENSOR_PIN);
    initProximitySensor(PROXIMITY_SENSOR_PIN);
    initSoundSensor(SOUND_SENSOR_PIN);

    stdio_init_all();

    // Create tasks
    xTaskCreate(motionSensorTask, "Motion Sensor Task", 256, NULL, 2, NULL);
    xTaskCreate(proximitySensorTask, "Proximity Sensor Task", 256, NULL, 2, NULL);
    xTaskCreate(soundSensorTask, "Sound Sensor Task", 256, NULL, 2, NULL);
    xTaskCreate(ledAndAlarmControlTask, "LED and Alarm Task", 256, NULL, 1, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
    return 0;
}

// Task to monitor motion sensor
void motionSensorTask(void *pvParameters) {
    while (1) {
        motionDetected = isMotionDetected();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task to monitor proximity sensor
void proximitySensorTask(void *pvParameters) {
    while (1) {
        proximityDetected = objectDetected();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task to monitor sound sensor
void soundSensorTask(void *pvParameters) {
    while (1) {
        uint16_t soundValue = readSoundSensor();
        if (soundValue >= HIGH_THRESHOLD) {
            soundDetected = 2;  // High sound
        } else if (soundValue >= MODERATE_THRESHOLD) {
            soundDetected = 1;  // Moderate sound
        } else {
            soundDetected = 0;  // Low sound
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task to control LEDs and alarm based on sensor states
void ledAndAlarmControlTask(void *pvParameters) {
    while (1) {
        if (motionDetected || proximityDetected || soundDetected == 2) {
            ledturnOn(LED1_PIN);
                        ledturnOn(LED2_PIN);

            setServoAngle(0.0);
            alarmturnOn();


        } else {
            ledturnOff(LED1_PIN);
                        ledturnOff(LED2_PIN);

            setServoAngle(90.0);
            alarmturnOff();
        }

        // if (proximityDetected) {
        //     ledturnOn(LED2_PIN);
        // } else {
        //     ledturnOff(LED2_PIN);
        // }

        // if (soundDetected == 1) {
        //     ledturnOn(LED3_PIN);
        //     vTaskDelay(pdMS_TO_TICKS(100));
        //     ledturnOff(LED3_PIN);
        // } else if (soundDetected == 2) {
        //     ledturnOn(LED3_PIN);
        // } else {
        //     ledturnOff(LED3_PIN);
        // }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
