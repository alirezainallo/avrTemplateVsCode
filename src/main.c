#include <avr/io.h>
#include <util/delay.h>
 
int main(void)
{
  DDRA = DDRB = DDRC = DDRD = 0xff;
  PORTA = PORTB = PORTC = PORTD = 0x00;

  while (1)
  {
    _delay_ms(500);
    PORTA ^= (1 << 1);
    _delay_ms(500);
  }
}
