# pomodoro-avr
### Summary
This project consist of a [Pomodoro Timer](https://en.wikipedia.org/wiki/Pomodoro_Technique), which uses a 7-segment LCD display driven by an 8-bit shift register, a push button and an active buzzer.

It was developed and compiled on Microchip Studio 7.0 and it runs on the Atmega328p.

* display.c contains the display driver
* shift_reg.c contains the shift register driver
* pomodoro.c handles the logic for the countdown and the timer itself
* avrlibc was used
### Interesting features
* It makes use of Sleep mode.
* Unused peripherals were disabled as a means to power saving.
* Time based interruptions from Timer/Counter 1 to refresh the LCD display and update the countdown.
* External Interrupts on interruption line 0, wired to a push-button to pause and resume countdown.

### Schematic
![pomodoro_schem](https://user-images.githubusercontent.com/67167458/203857150-5aecc6e4-78ab-4c4a-99f9-7201424c0bb1.jpg)
