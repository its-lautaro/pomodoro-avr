/*
 * shift_reg.c
 *
 * Simple shift register driver
 * Created: 11/16/2022 9:15:50 PM
 * Author: its-lautaro
 */
#include "utils.h"
#include "shift_reg.h"
static void shift();
static void clear();
static void show();

void SR_Init(){
	//config mcu pins
	SR_DDR |= (1 << SER) | (1 << _OE) | (1 << RCLK) | (1 << SRCLK) | (1 << _SRCLR);
	clear();
	//output enable
	SR_PORT &= ~(1 << _OE);
}

//Transmits a byte of data to shift registers, and outputs it through Qa-Qh pins
void SR_Send(uint8_t b){	
	clear();
	for(int i=0;i<8;i++){
		if ((b>>i) & 1) {
			SR_PORT |= (1 << SER);//write 1
		}else{
			SR_PORT &= ~(1 << SER);//write 0
		}
		shift();	
	}
	show();
}


static void shift(){
	SR_PORT |= (1 << SRCLK);
	//hold at least 20 ns
	SR_PORT &= ~(1 << SRCLK);
}

//Stores data from shift registers (outputs to Qa-Qh pins)
static void show(){
	SR_PORT |= (1 << RCLK);
	//hold at least 20 ns
	SR_PORT &= ~(1 << RCLK);
}

//Clears data
static void clear(){
	SR_PORT &= ~(1<<_SRCLR);
	//hold at least 20ns
	SR_PORT |= 1<<_SRCLR;
	show();
}