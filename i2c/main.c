/*
 * main.c
 *
 * Created: 11/30/2021 10:33:05 PM
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
#include "eeprom_hal.c"
#include "timer0_hal.c"
#include "i2c_hal.c"

#define RTC_ADDR (0x68)

uint8_t print_buf[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 0;
	uint16_t error = 0;
	uint16_t adc_val = 0;
	uint32_t holder = 0;
	uint32_t rtc_interval = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	
	usart_init(9600);
	adc_init();
	adc_pin_enable(ADC3_PIN);
	adc_pin_select(ADC3_PIN);
	timer0_init();
	i2c_init(100000); //100kHz
	
	uint8_t rtc_data[7] = {0x50,0x59,0x23,0x07,0x31,0x10,0x20};
		
	sei();
	usart_send_string((uint8_t*)start);
	
	adc_val = adc_convert();
	holder = millis();
	
	error = i2c_write(RTC_ADDR,0x00,rtc_data,sizeof(rtc_data));
	if(error != TWI_OK){
		memset(print_buf,0,sizeof(print_buf));
		sprintf((char*)print_buf,"%d error value %d\r\n",__LINE__,run);
		usart_send_string((uint8_t*)print_buf);
		while(1);
		
	}
	
	rtc_interval = millis();
	while (1)
	{
		if(millis_end(rtc_interval,500)){
			error = i2c_read(RTC_ADDR,0x00,rtc_data,sizeof(rtc_data));
			if(error != TWI_OK){
				memset(print_buf,0,sizeof(print_buf));
				sprintf((char*)print_buf,"%d error value %d\r\n",__LINE__,run);
				usart_send_string((uint8_t*)print_buf);
				while(1);
			}
			
			memset(print_buf,0,sizeof(print_buf));
			sprintf(print_buf,"\r20%02x/%02x/%02x %02x %02x:%02x:%02x",
			rtc_data[6],
			rtc_data[5],
			rtc_data[4],
			rtc_data[2],
			rtc_data[1],
			rtc_data[0]
			);
			
			usart_send_string((uint8_t*)print_buf);
			
			rtc_interval = millis();
		} 
		
		
		if(millis_end(holder,adc_val)){
			run++;
			PORTD &= 0x0F;
			PORTB &= 0xF0;
			PORTD |= ((run & 0x0F) << 4);
			PORTB |= ((run & 0xF0) >> 4);
			adc_val = adc_convert();
			holder = millis();
		}
	}
}



