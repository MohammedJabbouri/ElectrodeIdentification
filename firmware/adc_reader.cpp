#include <SPI.h>
#include "config.hpp"

void initADC() {
    pinMode(PIN_SPI_CS, OUTPUT);
    digitalWrite(PIN_SPI_CS, HIGH);
    SPI.begin();
    SPI.beginTransaction(SPISettings(SPI_CLOCK_HZ, MSBFIRST, SPI_MODE0));
}

int readADC(uint8_t channel) {
    uint8_t b0 = 0x01;
    uint8_t b1 = (0x08 | channel) << 4;
    uint8_t b2 = 0x00;

    digitalWrite(PIN_SPI_CS, LOW);
    SPI.transfer(b0);
    uint8_t r1 = SPI.transfer(b1);
    uint8_t r2 = SPI.transfer(b2);
    digitalWrite(PIN_SPI_CS, HIGH);

    return ((r1 & 0x03) << 8) | r2;
}

void capturesamples(int* buffer, uint16_t count) {
    for (uint16_t i = 0; i < count; i++) {
        buffer[i] = readADC(ADC_CHANNEL);
        delayMicroseconds(1000000 / SAMPLE_RATE_HZ);
    }
}
