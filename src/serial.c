#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "digital.h"
#include "serial.h"

#if defined(__AVR_ATmega2560__)
    #define F_CPU 16000000UL
    #define MAX_BAUDRATE 57600
    #define CALC_BAUDRATE(B) ((F_CPU/(16UL * B)) - 1)

#elif defined(__AVR_ATmega328p)
    #warning "You need to test this on a 328p"
    #define F_CPU 16000000UL
    #define MAX_BAUDRATE 9600
    #define CALC_BAUDRATE(B) (F_CPU/(16UL * B))

#else
    #error "Unsupported architecture"
#endif

#define RX_QUEUE_SIZE 32
struct isr_rx_queue {
    uint16_t start, size;
    char queue[RX_QUEUE_SIZE];
};

FILE __stdout;
FILE __sdterr;
FILE __stdin;
serial_t __stdout_serial;
serial_t __stdin_serial;
serial_t __stderr_serial;

struct isr_rx_queue __rx0_queue;
struct isr_rx_queue __rx1_queue;
struct isr_rx_queue __rx2_queue;
struct isr_rx_queue __rx3_queue;

serial_t initialize_serial_0(uint32_t baudrate)
{
    UBRR0H = CALC_BAUDRATE(baudrate) >> 8;
    UBRR0L = CALC_BAUDRATE(baudrate);
    UCSR0A &= ~(1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);


    serial_t s;
    s.state_reg = &UCSR0A;
    s.io_reg = &UDR0;
    s.tx_ready_field = UDRE0;
    s.rx_ready_field = RXC0;
    s.queue = &__rx0_queue;

    __rx0_queue.start = 0;
    __rx0_queue.size = 0;

    return s;
}

serial_t initialize_serial_1(uint32_t baudrate)
{
    UBRR1H = CALC_BAUDRATE(baudrate) >> 8;
    UBRR1L = CALC_BAUDRATE(baudrate);
    UCSR1A &= ~(1 << U2X1);
    UCSR1B = (1 << TXEN1) | (1 << RXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

    serial_t s;
    s.state_reg = &UCSR1A;
    s.io_reg = &UDR1;
    s.tx_ready_field = UDRE1;
    s.rx_ready_field = RXC1;
    s.queue = &__rx1_queue;

    __rx0_queue.start = 0;
    __rx0_queue.size = 0;

    return s;
}

serial_t initialize_serial_2(uint32_t baudrate)
{
    UBRR2H = CALC_BAUDRATE(baudrate) >> 8;
    UBRR2L = CALC_BAUDRATE(baudrate);
    UCSR2A &= ~(1 << U2X2);
    UCSR2B = (1 << TXEN2) | (1 << RXEN2) | (1 << RXCIE2);
    UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);

    serial_t s;
    s.state_reg = &UCSR2A;
    s.io_reg = &UDR2;
    s.tx_ready_field = UDRE2;
    s.rx_ready_field = RXC2;
    s.queue = &__rx2_queue;

    __rx2_queue.start = 0;
    __rx2_queue.size = 0;

    return s;
}

int serial_count_available(serial_t serial)
{
    return serial.queue->size;
}

void serial_put_char(serial_t serial, char c)
{
    loop_until_bit_is_set(*serial.state_reg, serial.tx_ready_field);
    *(serial.io_reg) = c;
}

unsigned char serial_get_char(serial_t serial)
{
    if (serial.queue->size == 0)
        return 0;

    char c = serial.queue->queue[serial.queue->start];
    serial.queue->start = (serial.queue->start + 1) % RX_QUEUE_SIZE;
    serial.queue->size--;
    return c;
}

static int io_putchar(char c, FILE *stream)
{
    if (stream == &__stdout)
        serial_put_char(__stdout_serial, c);
    return 1;
}

static int io_getchar(FILE *stream)
{
    if (stream == &__stdin)
        return serial_get_char(__stdin_serial);
    return 0;
}

void serial_init_usb(serial_t *out, serial_t *in)
{
#if defined(__AVR_ATmega2560__) || defined(__AVR__ATmega328p)
    serial_t s = initialize_serial_0(MAX_BAUDRATE);
    *out = s;
    *in = s;
#else
    #error "Unusupported architecture"
#endif

}

void serial_setup_stdio(serial_t out, serial_t in)
{
    FILE fout = FDEV_SETUP_STREAM(io_putchar, NULL, _FDEV_SETUP_WRITE);
    FILE fin = FDEV_SETUP_STREAM(NULL, io_getchar, _FDEV_SETUP_READ);
    __stdout = fout;
    __stdin = fin;

    stdout = &__stdout;
    stdin = &__stdin;

    __stdout_serial = out;
    __stdin_serial = in;
}

#define GENERATES_ISR_RX(Isr, Rx, UCSRA, RXC, UDR)               \
ISR(Isr)                                                         \
{                                                                \
    uint16_t id = (Rx.start + Rx.size) % RX_QUEUE_SIZE;          \
    Rx.queue[id] = UDR;                                          \
    if (Rx.size < RX_QUEUE_SIZE)                                 \
        Rx.size++;                                               \
}

GENERATES_ISR_RX(USART0_RX_vect, __rx0_queue, UCSR0A, RXC0, UDR0);
GENERATES_ISR_RX(USART1_RX_vect, __rx1_queue, UCSR1A, RXC1, UDR1);
GENERATES_ISR_RX(USART2_RX_vect, __rx2_queue, UCSR2A, RXC2, UDR2);
