#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <tmr1.h>

volatile uint64_t nowTime = 0;
volatile uint64_t prevTime = 0;

int main(void){
  
  DDRB |= (1 << 5);
  PORTB = 0x00;

  timer1_init();

  
  while(1){
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