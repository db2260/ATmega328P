//timer0_hal.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "timer0_hal.h"

volatile static uint32_t millis_c = 0;

ISR(TIMER0_COMPA_vect){
	millis_c++;
}

void timer0_init(){
	TCCR0A |= (1 << WGM01);
	OCR0A = 249;
	TIMSK0 |= (1 << OCIE0A);
	TCCR0B |= (0b011 << CS00);
	
}

uint32_t millis(void){
	return millis_c;
}

uint8_t millis_end(uint32_t start_time, uint32_t delay_time){
	return ((millis() - start_time) >= delay_time);
}