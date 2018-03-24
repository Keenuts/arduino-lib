#pragma once

#include <avr/io.h>

#define OUT 1
#define IN  0

#if defined(__AVR_ATmega328P__)
#define DATA_2 2
#define DATA_3 3
#define DATA_4 4
#define DATA_5 5
#define DATA_6 6
#define DATA_7 7
#define DATA_8 8
#define DATA_9 9
#define DATA_10 10
#define DATA_11 11
#define DATA_12 12
#define DATA_13 13

#define ANALOG_0 14
#define ANALOG_1 15
#define ANALOG_2 16
#define ANALOG_3 17
#define ANALOG_4 18
#define ANALOG_5 19
#define ANALOG_6 20
#define ANALOG_7 21

#define LED 13

#define IS_IN_PORTD_RANGE(pin) ((pin) <= 7)
#define IS_IN_PORTB_RANGE(pin) ((pin) >= 8 && (pin) <= 13)
#define IS_IN_PORTC_RANGE(pin) ((pin) >= 14 && (pin) <= 21

#define GET_PORTD_BASE(pin) (0)
#define GET_PORTB_BASE(pin) (8)
#define GET_PORTC_BASE(pin) (14)

#elif defined (__AVR_ATmega2560__)

#define DATA_2 2
#define DATA_3 3
#define DATA_4 4
#define DATA_5 5
#define DATA_6 6
#define DATA_7 7
#define DATA_8 8
#define DATA_9 9
#define DATA_10 10
#define DATA_11 11
#define DATA_12 12
#define DATA_13 13

#define ANALOG_0 82
#define ANALOG_1 83
#define ANALOG_2 84
#define ANALOG_3 85
#define ANALOG_4 86
#define ANALOG_5 87
#define ANALOG_6 88
#define ANALOG_7 89
#define ANALOG_8 90
#define ANALOG_9 91
#define ANALOG_10 92
#define ANALOG_11 93
#define ANALOG_12 94
#define ANALOG_13 95
#define ANALOG_14 96
#define ANALOG_15 97

#define IS_IN_PORTF_RANGE(pin) ((pin) >= ANALOG_0 && (pin) <= ANALOG_15)

#define GET_PORTF_BASE(pin) (ANALOG_0)

#endif

void digital_write(uint8_t pin, uint8_t value);
uint8_t digital_read(uint8_t pin);
void set_direction(uint8_t pin, uint8_t dir);

/*
 * direction: low = input | high = output
 * 
 *
 * PINS 8-13 | DIGITAL
 *
 * 		PORTB data			  RW
 * 		DDRB  direction   RW
 * 		DDB   direction port name
 * 		PINB  input       R-
 *
 * PINS 0-7 | DIGITAL
 * 		PORTD data				RW
 * 		DDRD  direction   RW
 * 		DDD   direction port name
 * 		PIND  input				R-
 *
 * PINS 0-5 | ANALOG
 * 		PORTC data				RW
 * 		DDRC  direction 	RW
 * 		DDC   direction port name
 * 		PINC  input 			R-
 *
 */
