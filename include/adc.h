#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init();
void adc_read(uint16_t* frame);

#endif