/*
 * main.c
 *
 * Created: 12/1/2021 12:03:22 PM
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
#include "spi_hal.c"


uint8_t print_buf[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	
	usart_init(9600);
	spi_master_init();
	
	uint16_t rx_data = 0;
	uint16_t tx_data = 0;
	
	sei();
	
	usart_send_string((uint8_t*)start);
		
	while (1)
	{
		usart_send_string("tx start ");
		tx_data++;
		spi_transfer(&tx_data, &rx_data, 1);
		
		if(tx_data >= 255){
			tx_data = 0;
		}
		
		memset(print_buf,0,sizeof(print_buf));
		sprintf(print_buf, "%c %d ",rx_data,tx_data);
		usart_send_string(print_buf);
		usart_send_string("\n\r");
		
		_delay_ms(200);
	}
}



