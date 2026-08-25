#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void adc_init(){
    /*
    PRADC = start conversion by clearing this and setting start conversion
    ADC prescaler is in ADCSRA 
    prescaler counts when ADEN is set in ADCSRA

    adc conversion takes 13 ADC clock cycles 
    25 cycles on the first start due to initialization 

    change channel after 1 ADC clock cycle after ADSC write

    Safe ways to chance ADMUX
    a. When ADATE or ADEN is cleared.
    b. During conversion, minimum one ADC clock cycle after the trigger event.
    c. After a conversion, before the Interrupt Flag used as trigger source is cleared.


    */

    ADCSRA |= // bit 2 to 0 
    /*
    000     2
    001     2
    010     4
            8
            16
            32
            64
            128
    */

    DIDR0 = 0x3F; // disable digital 

    ADCSRA &= ~(1 << 7); // ADCEN
    
    
}

void adc_read(uint16_t* frame){
    volatile uint8_t i;
    for(i = 0; i < 8; i++){
        ADMUX = (ADMUX & 0xF8) & (i & 0x07);
        ADCSRA |= (1 << 6); //conversion
        while(ADCSRA & (1 << 6));
        frame[i] = ADC;
    }

    
    return;
}