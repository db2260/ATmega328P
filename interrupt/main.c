/*
 * main.c
 *
 * Created: 11/28/2021 2:52:37 PM
 * Author : shini
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

volatile uint8_t counter = 0x10; //0b00010000

ISR(INT0_vect) {
	if(counter >= 0x80){
		counter = 0x10;
	}
	else{
		counter *= 2;
	}
}

ISR(INT1_vect) {
	if(counter <= 0x10){
		counter = 0x80;
	}
	else{
		counter /= 2;
	}
}

int main(void)
{
	DDRD &= 0xF3; //0b11110011
	DDRD |= 0xF0; //0b11110000
	
	PORTD = 0x0C; //0b00001100
	
	// INT0 and INT1 interrupts are triggered on the falling edge
	EICRA |= (1 << ISC11)| (1 << ISC01);
	
	EIMSK = 0x03; // 0b00000011
	
	sei();
	
    while (1) 
    {
		PORTD &= 0x0F; //0b00001111
		PORTD |= counter;
    }
}



