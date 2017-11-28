
#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <stdio.h>

#include "digital.h"
#include "serial.h"

FILE uart_output;
FILE uart_input;

int uart_putchar(char c, FILE *stream)
{
    (void)stream;
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 1;
}

int uart_getchar(FILE *stream)
{
    (void)stream;
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void uart_initialize(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

    //Enable RX + TX
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    FILE output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    FILE input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

    uart_output = output;
    uart_input = input;
    stdout = &uart_output;
    stdin = &uart_input;
}


#if 0
ISR(ADC_vect)
{
    glob = 1;
}
#endif

void softserial_init(softserial_t *ctx)
{
    set_direction(ctx->tx, OUT);
    set_direction(ctx->rx, IN);

    digital_write(ctx->tx, 1);
}

uint8_t softserial_read(softserial_t *ctx)
{

    (void)ctx;
    return 0;
}

void softserial_write(softserial_t *ctx, uint8_t data)
{
    (void)ctx;
    (void)data;
}

uint8_t softserial_available(softserial_t *ctx)
{
    uint8_t value = digital_read(ctx->rx);
    if (!value)
        return 1;
    return 0;
}
