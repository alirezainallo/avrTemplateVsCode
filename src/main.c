#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>


volatile uint64_t numOfTimOvf = 0;
void init_millis(void){
  TCCR2 = (1 << WGM21) | (1 << CS22);
  OCR2 = 124;

  TIMSK |= (1 << OCIE2);
  TCNT2 = 0;
}
uint64_t millis(void){
  uint64_t retVal = numOfTimOvf * 1 + TCNT2; // محاسبه تعداد میلی‌ثانیه
  return retVal;
}
ISR(TIMER2_COMP_vect){
  numOfTimOvf++; // افزایش شمارنده وقفه‌ها در هر بار وقوع وقفه
}

void heartBit(uint32_t ms){
  static uint64_t nextTick = 0;
  uint64_t currTick = millis();
  if(nextTick < currTick){
    nextTick = currTick + ms;
    PORTA ^= (1 << 1);
  }
}

int main(void){
  DDRA = DDRB = DDRC = DDRD = 0xff;
  PORTA = PORTB = PORTC = PORTD = 0x00;

  init_millis();
  sei();

  while(1){
    heartBit(500);
  }
}
