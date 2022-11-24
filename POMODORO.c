/*
 * pomodoro.c
 *
 * Pomodoro timer. It aids on time managing by breaking work into intervals (called pomodoros) typically 25 minutes in length.
 * separated by short breaks. The original technique indicates that after a fourth pomodoro is complete, it is to be followed
 * by a longer break. This pomodoro consists of 8 stages, which are 4 25 minutes intervals intercalated with short breaks.
 * The final stage consist of a long break.
 * Created: 11/22/2022 10:20:07 PM
 * Author: its-lautaro
 */ 
#include "utils.h"

#define POMODORO 25;
#define SHORT_BREAK 15;
#define LONG_BREAK 5;

static void new_stage();

int min;
int sec;

uint8_t stage_change; //state completion flag
uint8_t stage=0;

void PMDR_Init(){
	min=POMODORO;
	sec=0;
}
//flag used to pause the countdown on every stage completion
uint8_t PMDR_StageFlag(){
	return stage_change;
}
void PMDR_ClearFlag(){
	stage_change=0;
}
//get countdown current value
void PMDR_Read(uint8_t* min_r, uint8_t* sec_r){
	*min_r = min;
	*sec_r= sec;
}

void PMDR_Update(){
		sec--;
		
		if (sec<0){
			sec=59;
			min--;
		}
		
		if (min<0){
			new_stage();
			stage_change=1;
		}
}
//This function decides wether the next stage is a pomodoro or a break, and its length
static void new_stage(){
	stage++;
	if (stage>7){
		stage=0;
	}
	
	if (stage%2){
		if (stage==7){
			min=LONG_BREAK;
		}else{
			min=SHORT_BREAK;
		}
	}else{
		min=POMODORO;
	}
	
	sec=0;
}