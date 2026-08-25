#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void adc_init(){
    /*
    PRADC = start conversion by clearing this and setting start conversion
    ADC prescaler is in ADCSRA 
    prescaler counts when ADEN is set in ADCSRA

    adc conversion takes 13 ADC clock cycles 
    */

    //freq_adc = 16MHZ/prescaler
    // conversion time = 13 cycles / freq_adc
    //assuming 1kHz sampling 1ms between next sample
    // 8 channels --> 1ms/8 = 125us 
    // 104us @ 128 prescaler 
    ADCSRA |= 0x07; // bit 2 to 0 
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
    ADMUX |= (1 << 6);   // AVcc as Vref

    DIDR0 = 0x3F; // disable digital 

    ADCSRA |= (1 << 7); // ADCEN
    
    
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