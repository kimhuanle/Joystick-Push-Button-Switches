# ECE 387 Midterm Project
## Joystick, Push Button, and Emergency Stop Switch

## Author: Huan Le
## Date: 04/10/2022

# Table of Contents

* [Introduction](#Introduction)
* [Components](#Components)
* [Installation](#Installation)
* [Implementation](#Implementation)
* [Diagram](#Diagram)
* [Demonstration](#Demonstration)
--------------------
## Introduction
This is my Midterm project for class ECE 387. The purpose of this project is to interface a thumb joystick and an emergency stop switch with Arduino UNO R3 using only C programs and AVR toolchain. In this particular project that I designed, I was able to read the values of VarX and VarY, which represents the positions in X and Y coordinates of the joystick, and print them to LCD as well as using them to control 2 servo motors. The emergency stop switch was also added to allow for immediate shutdown of the whole circuit (including the Arduino).
## Components
* 1 x Arduino UNO R3<br><img src="https://umaine.edu/hackerspace/wp-content/uploads/sites/290/2017/11/ARDUINO_UNO_A06-300x211.png" width="300" height="200"/>
* 1 x Breadboard<br><img src="https://www.baldengineer.com/wp-content/uploads/2013/12/blank_breadboard.png" width="500" height="250"/>
* 1 x 9v Battery<br><img src="https://helptechco.com/files/522BP1_2.png" width="140" height="200"/>
* 1 x Potentiometer<br><img src="https://www.tube-town.net/ttstore/images/product_images/original_images/apo16-01_4.png" width="200" height="150"/>
* 2 x 1KΩ Resistor<br><br><img src="https://www.tandyonline.com/media/catalog/product/cache/f27cd47a8c413763245cb9dc18265f6f/2/7/271-1321-1k-carbon-resistors-sml.png" width="200" height="200"/>
* 20+ x Jumper Cables<br><img src="https://cdn.shopify.com/s/files/1/0410/7888/2465/products/genius-robotics-jumper-wires-40-pins-male-to-male-breadboard-jumper-wires-20cm-011-223-19245926088865_1024x.png?v=1631567860" width="300" height="300"/>
* 1 x LED<br><img src="https://hackster.imgix.net/uploads/attachments/446767/led_AOuhtzYEQe.png?auto=compress%2Cformat&w=200&h=150&fit=min"/>
* 1 x 16x2 LCD<br><br><img src="https://2.bp.blogspot.com/-2RywoglTPDA/WRnCAKzzkfI/AAAAAAAAD0A/F2BqYfEIQWMi0RdyDyA1Rdvcq9fyB_DdACLcB/s1600/lcd.png" width="400" height="170"/>
* 1 x Thumb joystick<br><br><img src="https://cdn-reichelt.de/bilder/web/xxl_ws/A300/KY-023.png" width="200" height="200"/>
* 2 x SG90 Servo Motor<br><img src="https://cdn.bodanius.com/media/1/a8e143943_Category_x.png" width="300" height="300"/>
* 1 x Emergency Stop Switch<br><br><img src="https://cdn-reichelt.de/bilder/web/xxl_ws/C200/A22NE-M-PXX2-N-B.png" width="300" height="300"/>
## Installation
You can clone this repository to test it out by running this command in your working directory:
```
git clone https://github.com/kimhuanle/Joystick-Push-Button-Switches.git
```
After that, run this command to compile and upload the code to your Arduino board:
```
python ./compile_script.py 4 com3
```
Note that the com3 is my com port, you have to change it to your actual com port.
## Implementation
* In order to use the emergency stop button to cut off power to the Arduino and the whole circuit, I connected the NC (Normally Closed) pins of the button in series with the red wire that connects the battery and the Arduino board.
* In order to read the X and Y values from the joystick, I did some research and used the functions from this blog [Using analog joystick in AVR projects](https://scienceprog.com/using-analog-joystick-in-avr-projects/). The function simply chooses the analog pin to convert front Analog signal to Digital signal using built-in ADC (Analog-to-Digital-Converter) of the ATmega328p. The ADC takes care of everything and we simply gets the final value as integer within range (0 - 1023).
* In order to display values to the LCD, I used the [HD44780](/libLCD/) library which was introduced by Dr. Jamieson in the previous labs.
* I also added the [USART](/libUSART/) library for sending values to the computer if hooking up an LCD is too exhausting. I commented out the part that use the USART communication in the program, but you can uncomment to use it. 
* In order to control the 2 servo motors, I used the 2 Timer1 OC1A and OC1B which directly control the outputs of PIN 9 and PIN 10 on the Arduino. The 2 Timers can generate PWM signal to the output pins. I did some calculation to find the perfect duty cycle for the SG90 servo and used a similar code to the PWM lab, except this time I used a 64 prescaler. There was also some calculations involved in calibrating the X, Y values to control the 2 servos.
* In order to compile the programs and upload the code to Arduino, I used the compile_script.py which was provided by Dr. Jamieson in the previous labs.
* Most of the implementation can be found in [joystick.c](/joystick.c) program. I also added some comments in there for description.
## Diagram
![Wiring Diagram](/diagram/my_diagram.png)
## Demonstration
* [Emergency Stop Switch Video](https://www.youtube.com/watch?v=vHGpFhmSoMw): This video demonstrates how the emergency stop button works. Also keep in mind that this video was recorded before I added the calibration and the servo motors interfacing.
* [Servo Motor Video](https://www.youtube.com/shorts/7ARIFFjL1rU): This video demonstrates how the joystick can control 2 servo motors and turn on an LED.
