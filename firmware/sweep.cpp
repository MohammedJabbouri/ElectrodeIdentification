#include <Arduino.h>
#include "config.hpp"

void initSweep() {
    pinMode(PIN_PWM_SWEEP, OUTPUT);
}

void setSweepFrequency(uint16_t freqHz) {
    uint32_t period = 1000000UL / freqHz;
    uint32_t halfPeriod = period / 2;

    digitalWrite(PIN_PWM_SWEEP, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(PIN_PWM_SWEEP, LOW);
    delayMicroseconds(halfPeriod);
}

void runSweep() {
    uint16_t stepSize = (SWEEP_FREQ_HIGH_HZ - SWEEP_FREQ_LOW_HZ) / SWEEP_STEPS;

    for (uint8_t i = 0; i < SWEEP_STEPS; i++) {
        uint16_t freq = SWEEP_FREQ_LOW_HZ + (i * stepSize);
        for (uint8_t cycles = 0; cycles < 5; cycles++) {
            setSweepFrequency(freq);
        }
        delay(SWEEP_STEP_DELAY_MS);
    }
}
