/*
 * pomodoro-timer.c
 *
 * Created: 11/16/2022 9:13:45 PM
 * Author : its-lautaro
 */ 
#include "utils.h"
#include "display.h"
#include "pomodoro.h"

#define DISP_REFRESH_RATE 125
#define BUZZ 10 //buzzer on/off frequency

static void WDT_off(void);
static void goSleep();

static uint8_t flag_B=0; //flag to enable the buzzer upon completion of a stage
static uint8_t B_Pulse=0; //rings the buzzer

static uint8_t flag_S=0; //flag to update time every second
static uint8_t flag_P=1; //flag to pause countdown

uint8_t min;
uint8_t sec;

int main(void)
{
	//Disable unused modules
	power_adc_disable();
	power_spi_disable();
	power_twi_disable();
	power_timer0_disable();
	power_usart0_disable();
	WDT_off();
	
	//Enable Timer1 interrupts (prescaler 256, ctc mode)
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 62500/DISP_REFRESH_RATE;
	
	//Enable external interrupt by low level on INT0 line
	DDRD &= (1<<2);
	EICRA |= (1<<ISC01)|(1<<ISC10);
	EIMSK |= (1<<INT0);
	
	//Buzzer pin
	DDRD |= (1<<PIND3);
	
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	int digit=1;
	LCD_Init();
	PMDR_Init();
	PMDR_Read(&min,&sec);
	LCD_SetTime(min, sec);
	
    while (1) 
    {
		cli();
		
		//refresh display
		if (digit>4){
			digit=1;
		}
		LCD_Refresh(digit);
		digit++;
		
		//update countdown
		if(flag_S & !(flag_P)){
			flag_B=0;
			flag_S=0;
			
			PMDR_Update();
			PMDR_Read(&min,&sec);
			
			LCD_SetTime(min, sec);		
			//detect stage completion
			if (PMDR_StageFlag()){
				PMDR_ClearFlag();
				flag_P=1; //pause countdown
				flag_B=1; //start buzzer
			}
		}
		
		if(flag_B){
			//turn buzzer on
			if (B_Pulse){
				PORTD |= (1<<PIND3);
			}
			//turn buzzer off
			else{ 
				PORTD &= ~(1<<PIND3);
			}
		}else{
			//turn buzzer off
			PORTD &= ~(1<<PIND3);
		}

		goSleep();
    }
}
//ensures to disable brown-out detection before going into sleep mode
//it also enables interruptions to be waken up by timer/push-button
static void goSleep(){
	sleep_enable();
	sleep_bod_disable();
	sei();
	sleep_cpu();
	sleep_disable();
}

// This function follows the procedure shown in datasheet's chapter 9 to disable the Watchdog Timer
static void WDT_off(void)
{
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Keep old prescaler setting to prevent unintentional time-out*/
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
}

ISR(TIMER1_COMPA_vect){
	static uint8_t countS=0;
	static uint8_t countB=0;
	
	countS++;
	countB++;
	//detects 1 second has elapsed
	if (countS == DISP_REFRESH_RATE){
		countS = 0;
		flag_S = 1;
	}
	//buzzer pulse generator
	if  (countB == BUZZ){
		countB = 0;
		B_Pulse ^=1;
	}
}
// detect button press
ISR(INT0_vect){
	//debounce and release detection
	_delay_ms(150); 
	while (PIND & (1<<PIND2));
	//toggle countdown pause
	flag_P ^=1; 
}