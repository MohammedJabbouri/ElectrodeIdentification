#pragma once
#include <stdint.h>

void initADC();
int readADC(uint8_t channel);
void captureSamples(int* buffer, uint16_t count);
