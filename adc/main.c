/*
 * main.c
 *
 * Created: 11/27/2021 6:30:55 PM
 * Author : shini
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart_hal.c"
#include "adc_hal.c"

uint8_t print_buf[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 1;
	uint16_t convert = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	
	//Initialize the serial port
	usart_init(9600);
	
	adc_init();
	adc_pin_enable(ADC5_PIN);
	adc_pin_select(ADC5_PIN);
	//adc_pin_enable(ADC5D);
	//adc_pin_select(0b101);
	
	//Enable global interrupts
	sei();
	
	usart_send_string((uint8_t*)start);
	
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
	
	while (1)
	{
		convert = adc_convert();
		float volts = ADC_VOLT(convert);
		memset(print_buf,0,sizeof(print_buf));
		sprintf((char*)print_buf,"ADC res:0x%04x V:%0.2f\r",convert,volts);
		usart_send_string(print_buf);
		
		run = convert >> 2;
		
		PORTD &= 0x0F;
		PORTB &= 0xF0;
		PORTD |= ((run & 0x0F) << 4);
		PORTB |= ((run & 0xF0) >> 4);
	}
}


