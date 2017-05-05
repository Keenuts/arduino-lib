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
#define ACK_DELAY 200


void zero_pins() {
	for (uint32_t i = 0; i < 10; i++)
		digitalWrite(DATA_2 + i, 0);
}

void pulse() {
	digitalWrite(E, 0);
	_delay_ms(1);
	digitalWrite(E, 1);
	_delay_ms(1);
	digitalWrite(E, 0);
	_delay_ms(200);
}

void reset() {
	zero_pins();
	digitalWrite(DATA0, 1);
	pulse();
	zero_pins();
}

void set_screen_status(int on, int cursor, int blink) {
	zero_pins();

	digitalWrite(RS, 0);
	digitalWrite(RW, 0);
	
	digitalWrite(DATA0, blink);
	digitalWrite(DATA1, cursor);
	digitalWrite(DATA2, on);
	digitalWrite(DATA3, 1);
	digitalWrite(DATA4, 0);
	digitalWrite(DATA5, 0);
	digitalWrite(DATA6, 0);
	digitalWrite(DATA7, 0);

	pulse();
	zero_pins();
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

	//_delay_ms(ACK_DELAY);
}

static void loop(void)
{
	//_delay_ms(BLINK_DELAY_MS);
}

int main (void)
{
	setup();
	reset();
	set_screen_status(0, 0, 0);
	set_screen_status(1, 0, 0);
	set_screen_status(1, 1, 0);


	while(1)
		loop();
}
