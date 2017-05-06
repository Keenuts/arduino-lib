#include <avr/io.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"

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
#define ACK_DELAY 1

static void zero_pins() {
	for (uint32_t i = 0; i < 8; i++)
		digitalWrite(DATA0 + i, 0);
}

static void pulse() {
	digitalWrite(E, 1);
	digitalWrite(E, 0);
	_delay_us(ACK_DELAY);
}

static void set_screen_status(int on, int cursor, int blink) {
	zero_pins();

	digitalWrite(DATA0, blink);
	digitalWrite(DATA1, cursor);
	digitalWrite(DATA2, on);
	digitalWrite(DATA3, 1);

	pulse();
}

void clear() {
	zero_pins();

	digitalWrite(DATA0, 1);
	pulse();
	_delay_ms(2.2);
}

void write_char(uint8_t c) {
	for (uint8_t i = 0; i < 8; i++, c = c >> 1)
		digitalWrite(DATA0 + i, c & 1);

	digitalWrite(E, 1);
	digitalWrite(E, 0);
	_delay_us(50);
}

void set_mode(uint8_t mode) {
	digitalWrite(RS, mode);
	_delay_us(50);
}

void power_on() {
	setDirection(ANALOG_0, OUT);
	for (uint8_t i = 0; i < 11; i++)
		setDirection(DATA_2 + i, OUT);
	
	zero_pins();
	set_screen_status(1, 0, 0);
	clear();

	_delay_ms(500);
	digitalWrite(ANALOG_0, 1);
}

void power_off() {
	digitalWrite(ANALOG_0, 0);
	set_screen_status(0, 1, 1);
	zero_pins();
}
