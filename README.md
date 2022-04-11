# ECE 387 Midterm Project
## Joystick, Push Button, and Emergency Stop Switch

## Author: Huan Le
## Date: 04/10/2022

# Table of Contents

* [Introduction](#Introduction)
* [Components](#Components)
* [Implementation](#Implementation)
* [Demonstration](#Demonstration)
--------------------
## Introduction
This is my Midterm project for class ECE 387. The purpose of this project is to interface a thumb joystick and an emergency stop switch with Arduino UNO R3 using only C programs and AVR toolchain. In this particular project that I designed, I was able to read the values of VarX and VarY, which represents the positions in X and Y coordinates of the joystick, and print them to LCD as well as using them to control 2 servo motors. The emergency stop switch was also added to allow for immediate shutdown of the whole circuit (including the Arduino).
## Components
* 1 x Arduino UNO R3
* 1 x Breadboard
* 1 x 9v Battery
* 1 x Potentiometer
* 2 x 1KΩ Resistor
* 20+ x Jumper Cables
* 1 x LED
* 1 x 16x2 LCD
* 1 x Thumb joystick
* 2 x SG90 Servo Motor
* 1 x Emergency Stop Switch 
## Implementation
* In order to use the emergency stop button to cut off power to the Arduino and the whole circuit, I connected the NC (Normally Closed) pins of the button in series with the red wire that connects the battery and the Arduino board.
* In order to read the X and Y values from the joystick, I did some research and used the functions from this blog [Using analog joystick in AVR projects](https://scienceprog.com/using-analog-joystick-in-avr-projects/). The function simply chooses the analog pin to convert front Analog signal to Digital signal using built-in ADC (Analog-to-Digital-Converter) of the ATmega328p. The ADC takes care of everything and we simply gets the final value as integer within range (0 - 1023).
* In order to display values to the LCD, I used the HD44780 library which was introduced by Dr. Jamieson in the previous labs.
* I also added the libUSART for sending values to the computer if hooking up an LCD is too exhausting. I commented out the part that use the USART communication in the program, but you can uncomment to use it. 
* In order to control the 2 servo motors, I used the 2 Timer1 OC1A and OC1B which directly control the outputs of PIN 9 and PIN 10 on the Arduino. The 2 Timers can generate PWM signal to the output pins. I did some calculation to find the perfect duty cycle for the SG90 servo and used a similar code to the PWM lab, except this time I used a 64 prescaler. There was also some calculations involved in calibrating the X, Y values to control the 2 servos.
* In order to compile the programs and upload the code to Arduino, I used the compile_script.py which was provided by Dr. Jamieson in the previous labs.
* Most of the implementation can be found in joystick.c program. I also added some comments in there for description.
## Demonstration
[Emergency Stop Switch Video](https://www.youtube.com/watch?v=vHGpFhmSoMw): This video demonstrates how the emergency stop button works. Also keep in mind that this video was recorded before I added the calibration and the servo motors interfacing.
[Servo Motor Video](https://www.youtube.com/shorts/7ARIFFjL1rU): This video demonstrates how the joystick can control 2 servo motors and turn on an LED.