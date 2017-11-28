#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"
#include "multiplexer.h"
#include "serial.h"
 
static void outb(uint16_t addr, uint8_t value)
{
    *((uint8_t*)addr) = value;
}

#define UBRRH 0x135
#define UBRRL 0x134

static void initialize_uart(uint16_t baudrate)
{
    outb(UBRRH, baudrate >> 8);
    outb(UBRRL, baudrate & 0xFF);
}

int main (void)
{
    initialize_uart(9600);
}
