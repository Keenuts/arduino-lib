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

int check(uint8_t val1, uint8_t val2,
		 uint8_t val3, uint8_t val4)
{
	if (val1 == 0 && val2 == 0 && val3 == 0 && val4 == 0)
		return 0;
	if (val1 == 1 && val2 == 1 && val3 == 1 && val4 == 1)
		return 0;
	if (val1)
		return 1;
	if (val2)
		return 2;
	if (val3)
		return 3;
	if (val4)
		return 4;
	return -1;
}

int __attribute__ ((noinline)) get_number(serial_t bt_serial, uint8_t *line,
					  uint8_t *column)
{
	(void)bt_serial;
	set_direction(ANALOG_0, IN);
	set_direction(ANALOG_1, IN);
	set_direction(ANALOG_2, OUT);
	set_direction(ANALOG_3, OUT);
	set_direction(ANALOG_4, OUT);
	set_direction(ANALOG_5, OUT);
	set_direction(ANALOG_6, IN);
	set_direction(ANALOG_7, IN);
	uint8_t val1 = 1;
	uint8_t val2 = 1;
	uint8_t val3 = 1;
	uint8_t val4 = 1;

	while (val1 + val2 + val3 + val4 != 1) {
		digital_write(ANALOG_2, 1);
		digital_write(ANALOG_3, 1);
		digital_write(ANALOG_4, 1);
		digital_write(ANALOG_5, 1);
		val1 = digital_read(ANALOG_0);
		val2 = digital_read(ANALOG_1);
		val4 = digital_read(ANALOG_6);
		val3 = digital_read(ANALOG_7);
	}

	*line = val1 ? 1 : (val2 ? 2 : (val3 ? 3 : 4));

	digital_write(ANALOG_2, 0);
	digital_write(ANALOG_3, 0);
	digital_write(ANALOG_4, 0);
	digital_write(ANALOG_5, 0);

	set_direction(ANALOG_0, OUT);
	set_direction(ANALOG_1, OUT);
	set_direction(ANALOG_2, IN);
	set_direction(ANALOG_3, IN);
	set_direction(ANALOG_4, IN);
	set_direction(ANALOG_5, IN);
	set_direction(ANALOG_6, OUT);
	set_direction(ANALOG_7, OUT);

	val1 = val2 = val3 = val4 = 1;
	while (val1 + val2 + val3 + val4 != 1) {
		digital_write(ANALOG_0, 1);
		digital_write(ANALOG_1, 1);
		digital_write(ANALOG_6, 1);
		digital_write(ANALOG_7, 1);
		val1 = digital_read(ANALOG_2);
		val2 = digital_read(ANALOG_3);
		val3 = digital_read(ANALOG_4);
		val4 = digital_read(ANALOG_5);
	}
	*column = val1 ? 1 : (val2 ? 2 : (val3 ? 3 : 4));

	digital_write(ANALOG_0, 0);
	digital_write(ANALOG_1, 0);
	digital_write(ANALOG_6, 0);
	digital_write(ANALOG_7, 0);
	return 0;
}

void __attribute__ ((noinline)) tarace(int a, serial_t bt_serial)
{
	set_direction(ANALOG_0, IN);
	set_direction(ANALOG_1, IN);
	set_direction(ANALOG_2, OUT);
	set_direction(ANALOG_3, OUT);
	set_direction(ANALOG_4, OUT);
	set_direction(ANALOG_5, OUT);
	set_direction(ANALOG_6, IN);
	set_direction(ANALOG_7, IN);
	digital_write(ANALOG_2, 1);
	digital_write(ANALOG_3, 1);
	digital_write(ANALOG_4, 1);
	digital_write(ANALOG_5, 1);

	uint8_t val1 = 1;
	uint8_t val2 = 1;
	uint8_t val3 = 1;
	uint8_t val4 = 1;

	while (val1 == 1 && val2 == 1 && val3 == 1 && val4 == 1) {
		val1 = digital_read(ANALOG_0);
		val2 = digital_read(ANALOG_1);
		val3 = digital_read(ANALOG_6);
		val4 = digital_read(ANALOG_7);
	}

	serial_put_char(bt_serial, val1 + '0');
	serial_put_char(bt_serial, val2 + '0');
	serial_put_char(bt_serial, val3 + '0');
	serial_put_char(bt_serial, val4 + '0');
	digital_write(ANALOG_2, 0);
	digital_write(ANALOG_3, 0);
	digital_write(ANALOG_4, 0);
	digital_write(ANALOG_5, 0);
	(void)a;
}

char pos_to_char(uint8_t line, uint8_t column)
{
	static char table[] = {
		'1', '2', '3', 'A', '4', '5', '6', 'B',
		'7', '8', '9', 'C', '*', '0', '#', '.'
	};
	return table[(line - 1) * 4 + column - 1];
}

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

	bt_serial = initialize_serial_0(9600);
	sei();

	serial_out(bt_serial, "SALUT\n");

	while(1) {
		uint8_t line, column = 0;
		uint8_t line2, column2 = 0;
		get_number(bt_serial, &line, &column);
		get_number(bt_serial, &line2, &column2);
		if (line != line2 || column != column2)
			continue;
		serial_put_char(bt_serial, pos_to_char(line, column));
		serial_put_char(bt_serial, '\r');
	}
		//tarace(column, bt_serial);
}

#else
#error "Unknown ARCH"
#endif
