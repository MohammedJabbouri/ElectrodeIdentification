cmake_minimum_required(VERSION 3.20)
project(chemprint_firmware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARDUINO_SDK_PATH "/usr/share/arduino" CACHE PATH "Path to Arduino SDK")

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${ARDUINO_SDK_PATH}/hardware/arduino/avr/cores/arduino
    ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/SPI/src
)

set(SOURCES
    adc_reader.cpp
    serial_out.cpp
    sweep.cpp
    trigger.cpp
)

add_executable(chemprint_firmware ${SOURCES})

target_compile_options(chemprint_firmware PRIVATE
    -Wall
    -Wextra
    -mmcu=atmega328p
    -DF_CPU=16000000UL
)
