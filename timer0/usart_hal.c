#define F_CPU 8000000L

#include "usart_hal.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile static uint8_t rx_buf[RX_BUF_SIZE] = {0};
volatile static uint16_t rx_count = 0;
volatile static uint8_t usart_tx_busy = 1;

ISR(USART_RX_vect){
	volatile static uint16_t pos = 0;
	
	rx_buf[pos] = UDR0;
	rx_count++;
	pos++;
	
	if(rx_buf[pos] >= RX_BUF_SIZE){
		pos = 0;
	}
}

ISR(USART_TX_vect){
	usart_tx_busy = 1;
}

void usart_init(uint32_t baud_rate){
	//Double the transfer rate for asynchronous communication
	UCSR0A |= (1<<U2X0);
	
	// dummy variable to hold the value of UBRR register
	uint8_t dummy_ubrr = (F_CPU/(8*baud_rate))-1;
	
	//Holds upper four bits (nibble) for setting the baud rate
	UBRR0H = (dummy_ubrr & 0x0F00) >> 8;
	
	//Holds lower 8 bits (byte) for setting the baud rate
	UBRR0L = (dummy_ubrr & 0x00FF);
	
	//Enable receiver and transmitter
	//Enable interrupts for both receiver and transmitter
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);
	
}

void usart_send_byte(uint8_t c){
	while(usart_tx_busy == 0);
	usart_tx_busy = 0;
	UDR0 = c;
}

void usart_send_array(uint8_t *c, uint16_t len){
	for(uint16_t i=0; i<len; i++){
		usart_send_byte(c[i]);
	}
}

void usart_send_string(uint8_t *c){
	uint16_t i = 0;
	
	do{
		usart_send_byte(c[i]);
		i++;
		
	}while(c[i] != '\0');
	
	usart_send_byte(c[i]);
	
}

uint16_t usart_read_count(void){
	return rx_count;
}

uint8_t usart_read(void){
	static uint16_t pos = 0;
	uint8_t data = 0;
	
	data = rx_buf[pos];
	pos++;
	rx_count--;
	if(pos >= RX_BUF_SIZE){
		pos = 0;
	}
	return data;
}