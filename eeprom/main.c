/*
 * main.c
 *
 * Created: 11/29/2021 9:43:05 PM
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
#include "eeprom_hal.c"

uint8_t print_buf[64] = {0};


int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 0;
	uint16_t error = 0;
		
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	
	usart_init(9600);
	
	sei();
	usart_send_string((uint8_t*)start);
	
	error = EEPROM_read(96,&run);
	
	memset(print_buf,0,sizeof(print_buf));
	sprintf((char*)print_buf,"%d value %d\r\n",__LINE__,run);
	usart_send_string(print_buf);
	
	uint8_t c = run+1;
	
	memset(print_buf,0,sizeof(print_buf));
	sprintf((char*)print_buf,"%d value %d\r\n",__LINE__,c);
	usart_send_string(print_buf);
	
	error = EEPROM_update(96,c);	
	
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
	
    while (1) 
    {
    }
}

