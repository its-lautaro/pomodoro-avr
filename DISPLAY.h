/*
 * DISPLAY.h
 *
 * Created: 11/17/2022 10:40:35 PM
 *  Author: Lautaro
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "74HC595.h"
#define DISP_PORT PORTD
#define DISP_DDR DDRD
#define DIG1 7
#define DIG2 6
#define DIG3 5
#define DIG4 4

void LCD_Init();
void LCD_Write(uint8_t dig, uint8_t num);
void LCD_Refresh(uint8_t dig);
#endif /* DISPLAY_H_ */