/*
 * main.c
 *
 * Created: 12/1/2021 12:58:53 PM
 * Author : shini
 */ 

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart_hal.c"
#include "adc_hal.c"
#include "i2c_hal.c"
#include "watchdog_timer_hal.c"
//#include "avr/wdt.h"

uint8_t print_buf[64] = {0};

int main(void)
{

	WDT_off(0);
	WDT_Prescaler_Change(0,wdt_timeout_2s);
	
	const uint8_t start[] = "\n\rProgram Start\n\r";
	 
	DDRD |= (1 << DDD7) | (1 << DDD6);
	
	for(uint16_t i = 0; i < 3; i++){ //4*3 = 1200ms
		PORTD |= (1 << PORTD7 | 1 << PORTD6);
		_delay_ms(200);
		PORTD &= ~(1 << PORTD7 | 1 << PORTD6);
		_delay_ms(200);
	}
	
	usart_init(9600);
	
	sei();
	
	usart_send_string((uint8_t*)start);
	
	while (1)
	{
		for(int i=0; i<15; i++){ //400*15 = 6000ms
			PORTD |= (1 << PORTD7);
			PORTD &= ~(1 << PORTD6);
			_delay_ms(200);
			PORTD |= (1 << PORTD5);
			PORTD &= ~(1 << PORTD7);
			_delay_ms(200);
			wdr();
			
		}
		break;
	}
	wdr();
	while(1)
	{	
	}
}




