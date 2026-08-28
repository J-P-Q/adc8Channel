#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init();
void adc_start(uint8_t channel);

#endif