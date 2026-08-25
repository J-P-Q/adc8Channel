#include <stdint.h>
#include <avr/io.h>

static volatile uint64_t msCounter = 0;

void timer1_init(){
    /*
    TCNT1 = counter
    OCR1x = holds stop value of counter
    OCIE1x = int enable flag
    OCF1x = flag (in TIFR1 reg)
    */

    // Clear timer on compare match mode
    TCCR1A &= 0x00; 
    TCCR1B |= 0x08; 

    // prescaler
    // fOCnx = f_clk / N * (1 + OCR)
    // 1kHz = 16MHz / 64 * (1 + 124)
    TCCR1B |= 0x03;
    /*
    001     1
    010     8
            64
            256
    101     1024
    */

    TCNT1 = 0x0000;
    OCR1A = 249;

    TIMSK1 |= 0x02; //OCIE1A 

    SREG |= 0x80; // GIE

    return;
}

ISR(TIMER1_COMPA_vect){
    msCounter ++;
    return;
}

uint64_t getTime(void){
    volatile uint64_t time;
    SREG &= ~0x80; 
    time = msCounter;
    SREG |= 0x80;
    return time;
}