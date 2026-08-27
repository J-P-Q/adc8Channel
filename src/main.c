#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <tmr1.h>
#include <adc.h>
#include <usart0.h> 

volatile uint64_t nowTime = 0;
volatile uint64_t prevTime = 0;

volatile uint16_t frame[8] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile uint8_t transmitReadyFlag = 0;
volatile uint16_t checkSum = 0; 

ISR(TIMER1_COMPA_vect){
  adc_read(frame);
  transmitReadyFlag = 1;
  return;
}


int main(void){
  DDRC &= ~0x1F; 
  DDRB |= (1 << 5);
  PORTB = 0x00;

  uint8_t frame1;
  uint8_t frame0;
  uint8_t checkSum1;
  uint8_t checkSum0;

  adc_init();
  usart0_init();
  timer1_init();

  TCNT1 = 249; // INT immediately

  while(1){
    if(transmitReadyFlag){
      //checkSum = 0;
      for(uint8_t i = 0; i < 8; i++){
        frame1 = (frame[i] >> 8) & 0xFF;
        frame0 = frame[i] & 0x00FF;
        usart0_transmit(frame0);
        usart0_transmit(frame1);

        //checkSum = checkSum + frame[i];
      }
      //checkSum1 = (checkSum >> 8) & 0xFF;
      //checkSum0 = checkSum & 0x00FF;
      //usart0_transmit(checkSum0);
      //usart0_transmit(checkSum1);
      transmitReadyFlag = 0;
    }
    
  }
    

  

  return 0;
}

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