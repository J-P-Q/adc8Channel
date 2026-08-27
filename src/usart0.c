#include <avr/interrupt.h>
#include <avr/io.h>


void usart0_init(){
    UCSR0B |= (1 << 3); // TX EN
    UCSR0C |= (3 << 1); // 8 bit data

    // 38.4k baud
    UBRR0 = 25;
    return;
}

void usart0_transmit(uint8_t data){
    while(!(UCSR0A & 0x20)); // data reg empty
    UDR0 = data;
    
    return;
}