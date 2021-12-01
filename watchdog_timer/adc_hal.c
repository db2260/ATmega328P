//adc_hal.c

#include "adc_hal.h"

volatile static uint8_t adc_convert_done = 1;

ISR(ADC_vect){
	adc_convert_done = 1;
}

void adc_init(void){
	ADMUX |= 1 << REFS0;
	
	ADCSRA |= 1 << ADEN | 1 << ADIE | 0b111 << ADPS0;
	
}

void adc_pin_enable(uint8_t pin){
	DIDR0 |= 1 << pin;
}

void adc_pin_disable(uint8_t pin){
	DIDR0 &= ~(1 << pin);
}

void adc_pin_select(uint8_t source){
	ADMUX &= 0XF0;
	ADMUX |= source;
}

uint16_t adc_convert(void){
	uint8_t adc_low = 0;
	uint8_t adc_high = 0;
	
	adc_convert_done = 0;
	
	ADCSRA |= 1 << ADSC;
	
	while(adc_convert_done == 0);
	
	adc_low = ADCL;
	adc_high = ADCH;
	
	return (adc_high << 8 | adc_low);
}
