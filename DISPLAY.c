/*
 * DISPLAY.c
 *
 * 7 Segment Display Driver
 * Created: 11/17/2022 9:06:26 PM
 * Author: its-lautaro
 */ 

#include "utils.h"
#include "DISPLAY.h"

static void off();
const uint8_t numbers[10] = {0b00000011,0b10011111,0b00100101,0b00001101,0b10011001,0b01001001,0b01000001,0b00011111,0b00000001,0b00011001};
uint8_t memory[4];

void LCD_Init()
{
	DDRD |= (1<<DIG1) | (1<<DIG2) | (1<<DIG3) | (1<<DIG4);
	SR_Init();
	LCD_Write(0,1);
	LCD_Write(1,2);
	LCD_Write(2,3);
	LCD_Write(3,4);
}

void LCD_Write(uint8_t dig, uint8_t num)
{
	if (num > 9) return;
	memory[dig]=numbers[num];
}

void LCD_Refresh(uint8_t dig){
	switch (dig)
	{
		case 1:
			off();
			SR_Send(memory[0]);
			DISP_PORT |= (1<<DIG1);
		break;
		case 2:
			off();
			SR_Send(memory[1] & ~(1)); //show decimal point (min/sec separator)
			DISP_PORT |= (1<<DIG2);
		break;
		case 3:
			off();
			SR_Send(memory[2]);
			DISP_PORT |= (1<<DIG3);
		break;
		case 4:
			off();
			SR_Send(memory[3]);
			DISP_PORT |= (1<<DIG4);
		break;
		default: break;
	}
}

static void off(){
	DISP_PORT &= ~(1<<DIG1);
	DISP_PORT &= ~(1<<DIG2);
	DISP_PORT &= ~(1<<DIG3);
	DISP_PORT &= ~(1<<DIG4);
}