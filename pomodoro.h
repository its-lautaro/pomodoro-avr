/*
 * pomodoro.h
 *
 * Created: 11/22/2022 10:20:07 PM
 * Author: its-lautaro
 */ 


#ifndef POMODORO_H_
#define POMODORO_H_

void PMDR_Update();
void PMDR_Read(uint8_t*, uint8_t*);
void PMDR_Init();
uint8_t PMDR_StageFlag();
void PMDR_ClearFlag();

#endif /* POMODORO_H_ */
