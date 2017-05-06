#include <avr/io.h>
#include <time.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"
 
#define BLINK_DELAY_MS 250

#define ECHO ANALOG_1
#define SIG ANALOG_2

uint8_t read_delay(uint32_t pin) {
	uint8_t res = 0;
	
	_delay_ms(10);
	uint32_t v = 0;
	while (v < 10000) {
		_delay_us(1);
		if (digitalRead(pin))
			res++;
		v++;
	}
	return res + 42;
}

char buffer[128];

void int_to_str_internal(uint32_t i, uint32_t *index) {
	if (i == 0)
		return;

	char c = '0' + (i % 10);
	int_to_str_internal(i / 10, index);
	buffer[(*index)++] = c;
}

void int_to_str(uint32_t i) {
	uint32_t index = 0;
	if (i == 0)
		buffer[0] = '0';
	else
		int_to_str_internal(i, &index);
}

int read_probe() {
	setDirection(ECHO, IN);
	setDirection(SIG, OUT);

	digitalWrite(SIG, 0);
	_delay_us(2);
	digitalWrite(SIG, 1);
	_delay_us(11);
	digitalWrite(SIG, 0);
	return read_delay(ECHO);
}

static uint32_t my_strlen(const char* str) {
	uint32_t len = 0;
	while(str[len] != 0)
		len++;
	return len;
}

int main (void)
{
	power_on();
	set_mode(WRITE);


	int_to_str(read_probe());
	for (uint32_t i = 0; i < my_strlen(buffer); i++)
		write_char(buffer[i]); 

	set_mode(READ);

	_delay_ms(5000);
	clear();
	power_off();
}
