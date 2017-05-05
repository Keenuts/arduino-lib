#include <avr/io.h>
#include <util/delay.h>

#include "digital.h"
 
#define BLINK_DELAY_MS 250

#define DATA0 DATA_5
#define DATA1 DATA_6
#define DATA2 DATA_7
#define DATA3 DATA_8
#define DATA4 DATA_9
#define DATA5 DATA_10
#define DATA6 DATA_11
#define DATA7 DATA_12

#define RS DATA_2
#define RW DATA_3
#define E DATA_4
#define ACK_DELAY 2


void zero_pins() {
	digitalWrite(RS, 0);
	digitalWrite(RW, 0);
	digitalWrite(E, 0);
	for (uint32_t i = 0; i < 10; i++)
		digitalWrite(DATA_2 + i, 0);
}

void pulse() {
	digitalWrite(E, 0);
	_delay_ms(1);
	digitalWrite(E, 1);
	_delay_ms(1);
	digitalWrite(E, 0);
	_delay_ms(ACK_DELAY);
	zero_pins();
}

void clear() {
	zero_pins();
	digitalWrite(DATA0, 1);

	pulse();
}

static void set_screen_status(int on, int cursor, int blink) {
	zero_pins();

	digitalWrite(RS, 0);
	digitalWrite(RW, 0);
	
	digitalWrite(DATA0, blink);
	digitalWrite(DATA1, cursor);
	digitalWrite(DATA2, on);
	digitalWrite(DATA3, 1);

	pulse();
}

void function_set(uint8_t multiline, uint8_t big_font) {
	zero_pins();
		
	digitalWrite(DATA2, big_font);
	digitalWrite(DATA3, multiline);
	digitalWrite(DATA4, 1);
	digitalWrite(DATA5, 1);
	pulse();
}

void write_char(uint8_t c) {
	zero_pins();
	digitalWrite(RS, 1); 

	for (uint8_t i = 0; i < 8; i++, c = c >> 1)
		digitalWrite(DATA0 + i, c & 1);
	
	pulse();
}

static void setup()
{
	setDirection(DATA0, OUT);
	setDirection(DATA1, OUT);
	setDirection(DATA2, OUT);
	setDirection(DATA3, OUT);
	setDirection(DATA4, OUT);
	setDirection(DATA5, OUT);
	setDirection(DATA6, OUT);
	setDirection(DATA7, OUT);
	setDirection(E, OUT);
	setDirection(RS, OUT);
	setDirection(RW, OUT);

	_delay_ms(ACK_DELAY);
}

#define DDRAM 1
#define CGRAM 0

void select_memory_area(uint8_t area) {
	zero_pins();
	if (area == DDRAM)
		digitalWrite(DATA7, 1);
	else
		digitalWrite(DATA6, 1);
	pulse();
}

int main (void)
{
	setup();
	set_screen_status(1, 1, 1);
	clear();
	_delay_ms(1000);
	for (int i = 0; i < 60; i++)
		write_char(40);
	//select_memory_area(DDRAM);
	//clear();

	const char* str = "abcdefghijkl";
	for (int i = 0; i < 12; i++)
		write_char(str[i]); 

	_delay_ms(5000);
	set_screen_status(0, 0, 0);
}
