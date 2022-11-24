/*
 * display.h
 *
 * 7 Segment Display Driver
 * Created: 11/17/2022 9:06:26 PM
 * Author: its-lautaro
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "shift_reg.h"
#define DISP_PORT PORTD
#define DISP_DDR DDRD
#define DIG1 7
#define DIG2 6
#define DIG3 5
#define DIG4 4

void LCD_Init();
void LCD_Refresh(uint8_t dig);
void LCD_SetTime(uint8_t min, uint8_t sec);
#endif /* DISPLAY_H_ */