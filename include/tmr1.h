#ifndef TMR1_C
#define TMR1_C

#include <stdint.h>
#include <avr/io.h>

void timer1_init();
uint64_t getTime(void);

#endif