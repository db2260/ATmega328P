#ifndef USART_HAL_H_
#define USART_HAL_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RX_BUF_SIZE 128

void usart_init(uint32_t baud_rate);
void usart_send_byte(uint8_t c);
void usart_send_array(uint8_t *c, uint16_t len);
void usart_send_string(uint8_t *c);
uint16_t usart_read_count(void);
uint8_t usart_read(void);

#endif