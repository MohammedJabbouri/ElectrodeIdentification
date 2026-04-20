#include <Arduino.h>
#include "config.hpp"

void initTrigger() {
    pinMode(PIN_TRIGGER, OUTPUT);
    digitalWrite(PIN_TRIGGER, LOW);
}

void fireTrigger() {
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(100);
    digitalWrite(PIN_TRIGGER, LOW);
}
