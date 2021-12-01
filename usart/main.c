/*
 * usart.c
 *
 * Created: 11/27/2021 6:30:55 PM
 * Author : shini
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart_hal.c"

uint8_t print_buf[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	
	uint8_t data = 'A';
	
	//Initialize the serial port
	usart_init(9600);
	
	//Enable global interrupts
	sei();
	
	usart_send_string((uint8_t*)start);
	
	while (1)
	{
		usart_send_byte(data);
		_delay_ms(500);
		data++;
		if(data > 'Z'){
			data = 'A';
		}
		
		if(usart_read_count() > 0){
			data = usart_read();
			usart_send_byte(data);
		}
	}
}


