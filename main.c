/*
 * pomodoro-timer.c
 *
 * Created: 11/16/2022 9:13:45 PM
 * Author : its-lautaro
 */ 
#include "utils.h"
#include "DISPLAY.h"

#define DISP_REFRESH_RATE 125

static void WDT_off(void);
static void goSleep();

int main(void)
{
	//Disable unused modules
	power_adc_disable();
	power_spi_disable();
	power_twi_disable();
	power_timer0_disable();
	power_usart0_disable();
	WDT_off();
	
	//Enable Timer1 interrupts every 8ms (prescaler 256, ctc mode)
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 62500/DISP_REFRESH_RATE;
	
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	int digit=1;
	LCD_Init();
    while (1) 
    {
		cli();
		
		if (digit>4){
			digit=1;
		}
		LCD_Refresh(digit);
		digit++;
		
		goSleep();
    }
}

static void goSleep(){
	sleep_enable();
	sleep_bod_disable();
	sei();
	sleep_cpu();
	sleep_disable();
}

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
	static uint8_t count=0;
	count++;
	//detect a second has elapsed
	if (count == DISP_REFRESH_RATE){
		count = 0;
		//timer.update
	}
}