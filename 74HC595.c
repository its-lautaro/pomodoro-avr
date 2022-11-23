/*
 * _74HC595.c
 *
 * Simple shift register driver
 * Created: 11/16/2022 9:15:50 PM
 * Author: its-lautaro
 */
#include "utils.h"
#include "74HC595.h"
static void shift();
static void clear();
static void show();

void SR_Init(){
	// set pins as output (1)
	SR_DDR |= (1 << SER) | (1 << _OE) | (1 << RCLK) | (1 << SRCLK) | (1 << _SRCLR);
	clear();
	//output enable
	SR_PORT &= ~(1 << _OE);
}

/************************************************************************/
/*Transmits a byte of data over SER line, and outputs it through Qa-Qh pins*/
/************************************************************************/
void SR_Send(uint8_t b){	
	clear();
	for(int i=0;i<8;i++){
		/*write bit to SER*/
		if ((b>>i) & 1) {
			SR_PORT |= (1 << SER);
		}else{
			SR_PORT &= ~(1 << SER);
		}
		shift();	
	}
	show();
}


static void shift(){
	SR_PORT |= (1 << SRCLK);
	//_delay_us(1); //hold at least 20 ns
	SR_PORT &= ~(1 << SRCLK);
}

/************************************************************************/
/* Moves data from shift registers top storage registers (Qa-Qh pins)*/
/************************************************************************/
static void show(){
	SR_PORT |= (1 << RCLK);
	//_delay_us(1); //hold at least 20 ns
	SR_PORT &= ~(1 << RCLK);
}
/************************************************************************/
/* Clears data from shift registers*/
/************************************************************************/
static void clear(){
	SR_PORT &= ~(1<<_SRCLR);
	//_delay_us(1); //hold at least 20ns
	SR_PORT |= 1<<_SRCLR;
	show();
}