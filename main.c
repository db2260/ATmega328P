/*
 * main.c
 *
 * Created: 11/29/2021 6:30:55 PM
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
#include "timer0_hal.c"

uint8_t print_buf[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 1;
	uint16_t adc_val = 0;
	uint32_t holder = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	
	usart_init(9600);
	
	adc_init();
	adc_pin_enable(ADC5_PIN);
	adc_pin_select(ADC5_PIN);
	//adc_pin_enable(ADC5D);
	//adc_pin_select(0b101);
	
	timer0_init();
	
	sei();
	
	usart_send_string((uint8_t*)start);
	
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
	
	adc_val = adc_convert();
	holder = millis();
	
	while (1)
	{
		if(millis_end(holder,adc_val)){
			run++;
			PORTD &= 0x0F;
			PORTB &= 0xF0;
			PORTD |= ((run & 0x0F) << 4);
			PORTB |= ((run & 0xF0) >> 4);
			
		}
	}
}


