#include "digital.h"
#include <stdbool.h>

static void pin_write(uint8_t pin, uint8_t value, bool set_dir)
{
#ifdef IS_IN_PORTA_RANGE
	if (IS_IN_PORTA_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRA |= _BV(pin - GET_PORTA_BASE(pin));
			else
				PORTA |= _BV(pin - GET_PORTA_BASE(pin));
		} else {
			if (set_dir)
				DDRA &= ~_BV(pin - GET_PORTA_BASE(pin));
			else
				PORTA &= ~_BV(pin - GET_PORTA_BASE(pin));
		}
	}
#endif
#ifdef IS_IN_PORTB_RANGE
	if (IS_IN_PORTB_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRB |= _BV(pin - GET_PORTB_BASE(pin));
			else
				PORTB |= _BV(pin - GET_PORTB_BASE(pin));
		} else {
			if (set_dir)
				DDRB &= ~_BV(pin - GET_PORTB_BASE(pin));
			else
				PORTB &= ~_BV(pin - GET_PORTB_BASE(pin));
		}
	}
#endif
#ifdef IS_IN_PORTC_RANGE
	if (IS_IN_PORTC_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRC |= _BV(pin - GET_PORTC_BASE(pin));
			else
				PORTC |= _BV(pin - GET_PORTC_BASE(pin));
		} else {
			if (set_dir)
				DDRC &= ~_BV(pin - GET_PORTC_BASE(pin));
			else
				PORTC &= ~_BV(pin - GET_PORTC_BASE(pin));
		}
	}
#endif
#ifdef IS_IN_PORTD_RANGE
	if (IS_IN_PORTD_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRD |= _BV(pin - GET_PORTD_BASE(pin));
			else
				PORTD |= _BV(pin - GET_PORTD_BASE(pin));
		} else {
			if (set_dir)
				DDRD &= ~_BV(pin - GET_PORTD_BASE(pin));
			else
				PORTD &= ~_BV(pin - GET_PORTD_BASE(pin));
		}
	}
#endif
#ifdef IS_IN_PORTE_RANGE
	if (IS_IN_PORTE_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRE |= _BV(pin - GET_PORTE_BASE(pin));
			else
				PORTE |= _BV(pin - GET_PORTE_BASE(pin));
		} else {
			if (set_dir)
				DDRE &= ~_BV(pin - GET_PORTE_BASE(pin));
			else
				PORTE &= ~_BV(pin - GET_PORTE_BASE(pin));
		}
	}
#endif
#ifdef IS_IN_PORTF_RANGE
	if (IS_IN_PORTF_RANGE(pin)) {
		if (value) {
			if (set_dir)
				DDRF |= _BV(pin - GET_PORTF_BASE(pin));
			else
				PORTF |= _BV(pin - GET_PORTF_BASE(pin));
		} else {
			if (set_dir)
				DDRF &= ~_BV(pin - GET_PORTF_BASE(pin));
			else
				PORTF &= ~_BV(pin - GET_PORTF_BASE(pin));
		}
	}
#endif
}

void digital_write(uint8_t pin, uint8_t value)
{
	pin_write(pin, value, 0);
}

void set_direction(uint8_t pin, uint8_t value)
{
	pin_write(pin, value, 1);
}

uint8_t pinRead(uint8_t pin)
{
#ifdef IS_IN_PORTA_RANGE
	if (IS_IN_PORTA_RANGE(pin))
		return (PINA >> (pin - GET_PORTA_BASE(pin))) & 1;
#endif
#ifdef IS_IN_PORTB_RANGE
	if (IS_IN_PORTB_RANGE(pin))
		return (PINB >> (pin - GET_PORTB_BASE(pin))) & 1;
#endif
#ifdef IS_IN_PORTC_RANGE
	if (IS_IN_PORTC_RANGE(pin))
		return (PINC >> (pin - GET_PORTC_BASE(pin))) & 1;
#endif
#ifdef IS_IN_PORTD_RANGE
	if (IS_IN_PORTD_RANGE(pin))
		return (PIND >> (pin - GET_PORTD_BASE(pin))) & 1;
#endif
#ifdef IS_IN_PORTE_RANGE
	if (IS_IN_PORTE_RANGE(pin))
		return (PINE >> (pin - GET_PORTE_BASE(pin))) & 1;
#endif
#ifdef IS_IN_PORTF_RANGE
	if (IS_IN_PORTF_RANGE(pin))
		return (PINF >> (pin - GET_PORTF_BASE(pin))) & 1;
#endif
	return 0;
}

uint8_t digital_read(uint8_t pin)
{
	return pinRead(pin);
}
