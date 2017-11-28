#pragma once

#include <stdio.h>

void uart_initialize(void);
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

typedef struct _softserial_t
{
    uint8_t tx;
    uint8_t rx;
    uint16_t speed;
} softserial_t;

void softserial_init(softserial_t *ctx);
uint8_t softserial_read(softserial_t *ctx);
void softserial_write(softserial_t *ctx, uint8_t data);
uint8_t softserial_available(softserial_t *ctx);
