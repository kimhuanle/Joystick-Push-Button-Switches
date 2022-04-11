#define __DELAY_BACKWARD_COMPATIBLE__
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libLCD/hd44780.h"
#include "libUSART/usart.h"

// Initialize X and Y values
int X_Val, Y_Val, X_Init, Y_Init;
double A1, B1;
int X_MIN = 0;
int Y_MIN = 0;
int X_MAX = 1023;
int Y_MAX = 1023;

void initADC()
{
    // Select Vref=AVcc
    ADMUX |= _BV(REFS0);
    // set prescaller to 128 and enable ADC
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

int readADC(uint8_t ADCchannel)
{
    // select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    // single conversion mode
    ADCSRA |= _BV(ADSC);
    // wait until ADC conversion is complete
    while (ADCSRA & _BV(ADSC))
        ;
    return ADC;
}

int main()
{
    // Setup USART for Serial Monitor
    // initUSART();
    // stdout = fdevopen(sendUSART, NULL); /// USART Sending And Receiving
    // stdin = fdevopen(NULL, receiveUSART);

    // Setup Analog-to-Digital Converter for X and Y
    initADC();
    // Setup LCD
    LCD_Setup();
    // Setup SW at pin13 (B, 5) to input
    DDRB &= ~_BV(PB5);
    // Setup LED at pin5 (D, 5) to output
    DDRD |= _BV(PD6);

    // Setup for 2 Servos
    DDRB |= _BV(PB1) | _BV(PB2); // OC1A | OC1B
    ICR1 = 4999;
    TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);          // Fast PWM, TOP ICR1
    TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS11) | _BV(CS10); // clk/64
    OCR1A = 400;
    OCR1B = 390;

    // Print two lines with class info to check if LCD working
    _delay_ms(500);
    LCD_Clear();
    _delay_ms(10);
    LCD_GotoXY(0, 0);
    LCD_PrintString("ECE387: ");
    LCD_PrintInteger(LCD_GetY());
    LCD_GotoXY(0, 1);
    LCD_PrintString("LCD[");
    LCD_PrintInteger(LCD_GetY());
    LCD_PrintString("] working!");
    _delay_ms(2000);

    X_Init = readADC(0);
    Y_Init = readADC(1);
    // Initialize screen for printing values
    LCD_Clear();
    LCD_GotoXY(0, 0);
    LCD_PrintString("X Val:");
    LCD_GotoXY(0, 1);
    LCD_PrintString("Y Val:");

    while (1) /// infinite  loop
    {
        // Get X, Y values
        X_Val = readADC(0) - X_Init;
        Y_Val = readADC(1) - Y_Init;
        _delay_ms(100);

        // Serial Print X and Y values
        // printf("X Value:\t%d\nY Value:\t%d\n\n", X_Val, Y_Val); /// Send All input information via USART
        // _delay_ms(100);

        if (X_Val < 0)
            A1 = 400 - (650 - 400) * ((double)X_Val / (X_MAX - X_Init));
        else if (X_Val > 0)
            A1 = 400 - (400 - 140) * ((double)X_Val / (X_Init - X_MIN));
        else
            A1 = 400;
        OCR1A = (int)A1;
        if (Y_Val < 0)
            B1 = 390 - (650 - 390) * ((double)Y_Val / (Y_MAX - Y_Init));
        else if (Y_Val > 0)
            B1 = 390 - (390 - 140) * ((double)Y_Val / (Y_Init - Y_MIN));
        else
            B1 = 390;
        OCR1B = (int)B1;

        // Print X, Y, and SW values to LCD
        LCD_GotoXY(6, 0);
        LCD_PrintInteger(X_Val);
        // LCD_PrintDouble(A1, 1);
        LCD_PrintString("   ");
        LCD_GotoXY(6, 1);
        LCD_PrintInteger(Y_Val);
        // LCD_PrintDouble(B1, 1);
        LCD_PrintString("   ");
        LCD_GotoXY(11, 0);
        LCD_PrintString("Press:");
        LCD_GotoXY(13, 1);
        // Check if joystick is pressed
        if (PINB & _BV(PINB5))
        {
            LCD_PrintInteger(0);
            PORTD &= ~_BV(PD6);  // Turn LED on
        }
        else
        {
            LCD_PrintInteger(1);
            PORTD |= _BV(PD6);  // Turn LED off
        }
    }
}