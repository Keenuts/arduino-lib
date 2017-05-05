#include "digital.h"

void digitalWrite(uint8_t pin, uint8_t value)
{
	if (pin <= 7)
	{
		if (value)
			PORTD |= _BV(pin);
		else
			PORTD &= ~_BV(pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		if (value)
			PORTB |= _BV(pin - 8);
		else
			PORTB &= ~_BV(pin - 8);
	}
	else if (pin >= 14 && pin <= 21)
	{
		if (value)
			PORTC |= _BV(pin - 14);
		else
			PORTC &= ~_BV(pin - 14);
	}
}

void setDirection(uint8_t pin, uint8_t dir)
{
	if (pin <= 7)
	{
		if (dir)
			DDRD |=  _BV(pin);
		else
			DDRD &= ~_BV(pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		if (dir)
			DDRB |=  _BV(pin - 8);
		else
			DDRB &= ~_BV(pin - 8);
	}
	else if (pin >= 14 && pin <= 21)
	{
		if (dir)
			DDRC |=  _BV(pin - 14);
		else
			DDRC &= ~_BV(pin - 14);
	}
}

uint8_t digitalRead(uint8_t pin)
{
	if (pin <= 7)
		return (PIND >> pin) & 1;
	else if (pin >= 8 && pin <= 13)
		return (PINB >> (pin - 8)) & 1;
	else if (pin >= 14 && pin <= 21)
		return (PINC >> (pin - 14)) & 1;
	return 0;
}
