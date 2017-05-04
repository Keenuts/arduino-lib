#include <avr/io.h>
#include <util/delay.h>

#include "digital.h"
 
#define BLINK_DELAY_MS 1000


void setup();
void loop();

void setup()
{
	setDirection(LED, OUT);

	setDirection(DATA_3, OUT);
	setDirection(DATA_4, OUT);
	setDirection(DATA_5, OUT);
}

void PowerOn() {
	digitalWrite(DATA_3, 1);
	digitalWrite(DATA_4, 1);
	digitalWrite(DATA_5, 1);
}

void loop(void)
{
	static uint8_t state = 0;

	digitalWrite(LED, state);

	state = !state;
	_delay_ms(BLINK_DELAY_MS);
}

int main (void)
{
	setup();
	PowerOn();

	while(1)
		loop();
}
