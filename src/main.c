//#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"
#include "multiplexer.h"
#include "serial.h"

#if defined(__AVR_ATmega328P__)

int main(void)
{
	set_direction(DATA_3, OUT);

	while (1) {
		_delay_ms(500);
		digital_write(DATA_3, 0);
		_delay_ms(500);
		digital_write(DATA_3, 1);
	}
}

#elif defined(__AVR_ATmega2560__)

int main(void)
{
	//serial_t out, in, bt_serial;
	serial_t bt_serial;

	//serial_init_usb(&out, &in);
	//serial_setup_stdio(out, in);

	bt_serial = initialize_serial_1(9600);
	sei();

	serial_out(bt_serial, "Hello the " __DATE__ " at " __TIME__);

	while (1) {
		while (serial_count_available(bt_serial)) {
			char c = serial_get_char(bt_serial);
			serial_put_char(bt_serial, c);
		}
	}
}

#else
	#error "Unknown ARCH"
#endif
