#include <Arduino.h>
#include "config.hpp"
#include "adc_reader.hpp"
#include "trigger.hpp"

static int sampleBuffer[CAPTURE_SAMPLES];

void initSerial() {
    Serial.begin(BAUD_RATE);
    while (!Serial);
}

void sendSamples() {
    fireTrigger();
    captureSamples(sampleBuffer, CAPTURE_SAMPLES);

    Serial.println("BEGIN");
    for (uint16_t i = 0; i < CAPTURE_SAMPLES; i++) {
        Serial.println(sampleBuffer[i]);
    }
    Serial.println("END");
}

void waitForCommand() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        if (cmd == "CAPTURE") {
            sendSamples();
        } else if (cmd == "SWEEP") {
            runSweep();
            sendSamples();
        }
    }
}
