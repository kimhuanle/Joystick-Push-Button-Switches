#define __DELAY_BACKWARD_COMPATIBLE__
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libLCD/hd44780.h"
#include "libUSART/usart.h"

// Initialize X and Y values
uint16_t X_Val, Y_Val;

void initADC()
{
    // Select Vref=AVcc
    ADMUX |= _BV(REFS0);
    // set prescaller to 128 and enable ADC
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

uint16_t readADC(uint8_t ADCchannel)
{
    // select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    // single conversion mode
    ADCSRA |= _BV(ADSC);
    // wait until ADC conversion is complete
    while (ADCSRA & _BV(ADSC)) ;
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
    DDRB &= ~_BV(PORTB5);

    // Print two lines with class info to check if LCD working
    _delay_ms(100);
    LCD_Clear();
    _delay_ms(100);
    LCD_GotoXY(0, 0);
    LCD_PrintString("ECE387: ");
    LCD_PrintInteger(LCD_GetY());
    LCD_GotoXY(0, 1);
    LCD_PrintString("LCD[");
    LCD_PrintInteger(LCD_GetY());
    LCD_PrintString("] working!");
    _delay_ms(2000);
    
    // Initialize screen for printing values
    LCD_Clear();
    LCD_GotoXY(0, 0);
    LCD_PrintString("X Val:");
    LCD_GotoXY(0, 1);
    LCD_PrintString("Y Val:");

    while (1) /// infinite  loop
    {
        // Get X value
        X_Val = readADC(0b0);
        // Get Y value
        Y_Val = readADC(0b1);
        _delay_ms(100);
        
        // Serial Print X and Y values
        // printf("X Value:\t%d\nY Value:\t%d\n\n", X_Val, Y_Val); /// Send All input information via USART
        // _delay_ms(100);
        
        // Print X, Y, and SW values to LCD
        LCD_GotoXY(6, 0);
        LCD_PrintInteger(X_Val);
        LCD_PrintString("   ");
        LCD_GotoXY(6, 1);
        LCD_PrintInteger(Y_Val);
        LCD_PrintString("   ");
        LCD_GotoXY(11, 0);
        LCD_PrintString("Press:");
        LCD_GotoXY(13, 1);
        if (PINB & _BV(PINB5))
            LCD_PrintInteger(0);
        else
            LCD_PrintInteger(1);
    }
}