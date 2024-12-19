cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set the project name and specify the C and C++ standards
project(rp2040-freertos-template C CXX ASM)
set(CMAKE_C_STANDARD 11)   # Using C11 standard
set(CMAKE_CXX_STANDARD 17) # Using C++17 standard

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mlong-calls")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlong-calls")

# Initialize the Pico SDK
pico_sdk_init()

# Include paths
include_directories(
    ${PICO_SDK_PATH}/pico-sdk/src
    ${PICO_SDK_PATH}/hardware
    ${CMAKE_CURRENT_LIST_DIR} # Include current directory for local headers
    config                    # Directory for configuration headers
)

# Add the executable and specify all source files needed
add_executable(rp2040-freertos-template
    main.c
    LED_ctrl.c
    motion_sensor.c
    proximity_sensor.c
    servo_ctrl.c
    alarm_ctrl.c
    sound_sensor.c
)

# Link the required libraries
target_link_libraries(rp2040-freertos-template
    pico_stdlib
    hardware_adc
    hardware_pwm
    FreeRTOS-Kernel-Heap4 # Link FreeRTOS as specified in the new configuration
)

# Generate additional output files (map, bin, hex, uf2)
pico_add_extra_outputs(rp2040-freertos-template)

# Configure the output for USB and disable UART output
pico_enable_stdio_usb(rp2040-freertos-template 1)
pico_enable_stdio_uart(rp2040-freertos-template 0)
