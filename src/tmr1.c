#include <stdint.h>
#include <avr/io.h>

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
    TCCR1B |= 0x01;
    /*
    001     1
    010     8
            64
            256
    101     1024
    */

    TCNT1 = 0x0000;
    OCR1A = 0x00FF;

    TIMSK1 |= 0x02; //OCIE1A 


    return;
}