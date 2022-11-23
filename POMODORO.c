/*
 * pomodoro.c
 *
 * Created: 11/22/2022 10:20:07 PM
 * Author: Lautaro
 */ 
#include "utils.h"
uint8_t min;
uint8_t sec;

uint8_t stage;

const uint8_t pomodoro_m = 25;
const uint8_t short_break = 5;
const uint8_t long_break = 15;

void PMDR_Init(){
	min=25;
	sec=0;
}

void PMDR_SetTime(uint8_t tmin, uint8_t tsec){
	min = tmin;
	sec = tsec;
}

void PMDR_Update(){
}