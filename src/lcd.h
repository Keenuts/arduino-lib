#pragma once

#include <avr/io.h>

#define READ 0
#define WRITE 1

void clear();
void write_char(uint8_t c);
void set_mode(uint8_t mode);
void power_on();
void power_off();
