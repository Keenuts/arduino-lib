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

 
int main (void)
{
    serial_t out, in, bt_serial;

    serial_init_usb(&out, &in);
    serial_setup_stdio(out, in);
    bt_serial = initialize_serial_2(9600);
    
    sei();

    puts("Hello the " __DATE__ " at " __TIME__);

    while (1) {
        while (serial_count_available(bt_serial))
        {
            char c = serial_get_char(bt_serial);
            putchar(c);
            serial_put_char(bt_serial, c);
        }
    }
}
