/*
 * display.c
 *
 * 7 Segment Display Driver
 * Created: 11/17/2022 9:06:26 PM
 * Author: its-lautaro
 */ 

#include "utils.h"
#include "display.h"

static void off();
static void LCD_Write(uint8_t, uint8_t);
//handy array with the LED combination for every number (since display is common catode LEDs turn on low output)
const uint8_t numbers[10] = {0b00000011,0b10011111,0b00100101,0b00001101,0b10011001,0b01001001,0b01000001,0b00011111,0b00000001,0b00011001};
//it stores last assignated number for every digit (1 - 4)
uint8_t memory[4];

void LCD_Init()
{
	//config mcu pins
	DDRD |= (1<<DIG1) | (1<<DIG2) | (1<<DIG3) | (1<<DIG4);
	SR_Init();
	//zero-out display
	for (int i=0;i<4;i++){
		LCD_Write(i,0);
	}
}

static void LCD_Write(uint8_t dig, uint8_t num)
{
	if (num > 9) return; //avoid index out of bound
	
	memory[dig]=numbers[num];
}

//Write minutes and seconds to display
void LCD_SetTime(uint8_t min, uint8_t sec){
	LCD_Write(3,sec%10);
	sec=sec/10;
	LCD_Write(2,sec);
				
	LCD_Write(1,min%10);
	min=min/10;
	LCD_Write(0,min);
}
//This function runs every clock tick, it lights up the corresponding LEDs for the digit selected.
//It is intended to be called four times (once for every digit), once per clock tick.
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
//turns display off
static void off(){
	DISP_PORT &= ~(1<<DIG1);
	DISP_PORT &= ~(1<<DIG2);
	DISP_PORT &= ~(1<<DIG3);
	DISP_PORT &= ~(1<<DIG4);
}
