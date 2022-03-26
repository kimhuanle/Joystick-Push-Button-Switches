#include "usart.h"

void initUSART(void)
{
    // Set baud rate
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
    // enable transmission and reception
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
}

int sendUSART(char c, FILE *stream)
{
    // Step 1.  Wait until UDRE0 flag is high. Busy Waiting
    while (!(UCSR0A & _BV(UDRE0)));
    // Step 2. Write char to UDR0 for transmission
    UDR0 = c;
    return UDR0;
}

int receiveUSART(FILE *stream)
{
    // Step 1. Wait for Receive Complete Flag is high. Busy waiting
    while (!(UCSR0A & _BV(RXC0)));
    // Step 2. Get and return received data from buffer
    return UDR0;
}
