# McuBlink
Example applications and makefiles for various microcontroller boards

The McuBlink repository collects examples for programming 
microcontrollers at a low level using C++ and uploading those programs 
using `make`.  These programs are reimplementations of the Arduino 
"Blink" demo, periodically toggling an on-board LED on and off using 
timer/counter interrupts.  The current target hardware are AVR breakout 
boards from [Adafruit](https://www.adafruit.com/).

The goal is to facilitate starting new microcontroller programming 
projects without using the Arduino IDE or Wiring library.  For each 
board, the repository provides a makefile for compiling and uploading 
raw C++ code to the board and some minimal example code illustrating the 
use of interrupts and GPIO pins.  By writing to the board's LED pin, one 
can easily test whether the pipeline is working.

## Requirements
* `avr-gcc` and `avr-libc`
* `make`
* `avrdude`
