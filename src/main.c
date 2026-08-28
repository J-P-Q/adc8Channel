#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <tmr1.h>
#include <adc.h>
#include <usart0.h> 

volatile uint64_t nowTime = 0;
volatile uint64_t prevTime = 0;

volatile uint8_t ringBuffer[32];
volatile uint8_t usartIndex = 0;
volatile uint8_t adcIndex = 0;
volatile uint8_t count = 0; //Total in ring buffer

volatile uint16_t data = 0;
volatile uint8_t data1 = 0;
volatile uint8_t data0 = 0;

volatile uint8_t channel = 0;

//volatile uint8_t usartTest = 0xff;                                //FOR TESTING

ISR(TIMER1_COMPA_vect){
  adc_start(channel);
  //usart0_transmit(usartTest);                                     // FOR TESTING
  return;
}

ISR(ADC_vect){
  data = ADC;

  if(channel < 7){
   channel++;
   adc_start(channel); 
  }

  else{
    channel = 0;
  }

  data1 = (data >> 8) & 0xFF;
  data0 = data & 0x00FF;
  
  ringBuffer[adcIndex] = data1;
  count++;
  adcIndex = (adcIndex + 1)%32;

  ringBuffer[adcIndex] = data0;
  count++;
  adcIndex = (adcIndex + 1)%32;

  UCSR0B |= (1 << UDRIE0);    // Enable usart int
  return;
}

ISR(USART_UDRE_vect){
  if(count > 0){
    usart0_transmit(ringBuffer[usartIndex]);
    usartIndex = (usartIndex + 1)%32;
    count--;
    //usartTest--;                                                  // FOR TESTING
  }
  else{
    UCSR0B &= ~(1 << UDRIE0); //disable usart int 
  }
  return; 
}

int main(void){
  DDRC &= ~0x1F; 
  DDRB |= (1 << 5);
  PORTB = 0x00;

  adc_init();
  usart0_init();
  timer1_init();

  TCNT1 = 249; // INT immediately

  while(1){
    
  }
    
  return 0;
}

/*
void testTimer(void){
  nowTime = getTime();
  if(((uint64_t) nowTime - prevTime) >= 1000){
    PORTB ^= (1 << 5);
    prevTime = nowTime;

  }
  return;
}

void testTransmit(void){
  for(uint8_t i = 0; i < 0xFF; i+=16){
    usart0_transmit(i);
  }
  return;
}
*/