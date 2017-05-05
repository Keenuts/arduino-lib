#include <avr/io.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"
 
#define BLINK_DELAY_MS 250


int main (void)
{
	power_on();

	set_mode(WRITE);

	const char* str = "Va niquer ta mere.";
	for (int i = 0; i < 18; i++)
		write_char(str[i]); 

	set_mode(READ);

	_delay_ms(5000);
	power_off();
}
