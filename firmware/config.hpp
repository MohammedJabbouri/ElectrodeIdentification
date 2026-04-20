#pragma once

#define SAMPLE_RATE_HZ      75000
#define BAUD_RATE           115200
#define ADC_CHANNEL         0
#define SPI_CLOCK_HZ        1350000

#define PIN_SPI_CS          10
#define PIN_SPI_MOSI        11
#define PIN_SPI_MISO        12
#define PIN_SPI_CLK         13

#define PIN_TRIGGER         7
#define PIN_PWM_SWEEP       9

#define SWEEP_FREQ_LOW_HZ   10
#define SWEEP_FREQ_HIGH_HZ  5000
#define SWEEP_STEPS         60
#define SWEEP_STEP_DELAY_MS 10

#define SERIAL_BUFFER_SIZE  256
#define CAPTURE_SAMPLES     1000
