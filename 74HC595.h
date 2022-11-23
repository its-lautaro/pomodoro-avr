/*
 * _74HC595.h
 *
 * Simple shift register driver
 * Created: 11/16/2022 9:15:50 PM
 * Author: its-lautaro
 */ 


#ifndef _74HC595_H_
#define _74HC595_H_

#define SR_PORT PORTB
#define SR_DDR DDRB
#define SER 5
#define _OE 4 //output enable (low)
#define RCLK 3 //storage register clock
#define SRCLK 2 //shift register clock
#define _SRCLR 1 //shift register clear
void SR_Test();
void SR_Init();
void SR_Send(uint8_t b);


#endif /* 74HC595_H_ */