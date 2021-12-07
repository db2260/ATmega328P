/*
 * main.c
 *
 * Created: 12/3/2021 9:43:50 PM
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
#include "timer0_hal.c"
#include "timer1_hal.c"

int main(void)
{

	usart_init(9600);
	pwm_init();
	
	sei();
	
	servo_set(0,180);
	uint16_t i = 0;
	
    while (1) 
    {
		for(i = 0; i <= 180; i++){
			servo_set(i,180);
			_delay_ms(40);
		}
		
		for(i = 180; i >= 0 ; i--){
			servo_set(i,180);
			_delay_ms(40);
		}
		
	}
}

