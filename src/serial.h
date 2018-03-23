#pragma once

#include <stdio.h>

typedef struct
{
    volatile uint8_t *io_reg;
    volatile uint8_t *state_reg;

    uint8_t tx_ready_field;
    uint8_t rx_ready_field;
    struct isr_rx_queue *queue;
} serial_t;

serial_t initialize_serial_0(uint32_t baudrate);
serial_t initialize_serial_1(uint32_t baudrate);
serial_t initialize_serial_2(uint32_t baudrate);

int serial_count_available(serial_t serial);
unsigned char serial_get_char(serial_t serial);
void serial_put_char(serial_t serial, char c);
uint32_t serial_out(serial_t serial, const char* str);


void serial_init_usb(serial_t *out, serial_t *in);
void serial_setup_stdio(serial_t out, serial_t in);
