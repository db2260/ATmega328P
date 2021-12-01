#ifndef TIMER0_HAL_H_
#define TIMER0_HAL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer0_init();
uint32_t millis();
uint8_t millis_end(uint32_t start_time, uint32_t delay_time);

#endif