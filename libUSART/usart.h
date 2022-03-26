#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

#include <stdio.h>
#include <inttypes.h>
#include <avr/io.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void initUSART(void);
int sendUSART(char c, FILE *stream);
int receiveUSART(FILE *stream);

#endif